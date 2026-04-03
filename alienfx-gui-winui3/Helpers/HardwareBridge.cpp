#include "pch.h"
#include "Helpers/HardwareBridge.h"

extern "C" {
#include "../AlienFX-SDK/AlienFX_SDK/alienfx_sdk.h"
}

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winrt::AlienFX::Helpers
{
    HardwareBridge& HardwareBridge::Instance()
    {
        static HardwareBridge instance;
        return instance;
    }

    void HardwareBridge::Initialize(ConfigHandler* conf, FXHelper* fxhl, EventHandler* eve)
    {
        m_conf = conf;
        m_fxhl = fxhl;
        m_eve = eve;
    }

    IAsyncAction HardwareBridge::SetLightAsync(
        int32_t deviceId, int32_t lightId, winrt::Windows::UI::Color color)
    {
        if (m_fxhl) {
            m_fxhl->SetLight(deviceId, lightId, color.R, color.G, color.B);
            m_fxhl->UpdateColors(deviceId);
        }
        co_return;
    }

    IAsyncAction HardwareBridge::UpdateGlobalEffectAsync(
        int32_t deviceId, int32_t effectType)
    {
        if (m_fxhl) {
            m_fxhl->SetEffect(deviceId, effectType);
            m_fxhl->UpdateColors(deviceId);
        }
        co_return;
    }

    IVectorView<int32_t> HardwareBridge::GetDevices()
    {
        std::vector<int32_t> devices;
        if (m_fxhl) {
            for (int32_t i = 0; i < m_fxhl->GetDeviceCount(); ++i)
                devices.push_back(i);
        }
        return single_threaded_vector<int32_t>(std::move(devices)).GetView();
    }

    IVectorView<SensorData> HardwareBridge::GetSensors()
    {
        std::vector<SensorData> sensors;
        if (m_conf) {
            for (int32_t i = 0; i < m_conf->GetSensorCount(); ++i) {
                sensors.push_back(SensorData{
                    m_conf->GetSensorName(i),
                    m_conf->GetSensorValue(i),
                    L"\u00b0C"
                });
            }
        }
        return single_threaded_vector<SensorData>(std::move(sensors)).GetView();
    }

    void HardwareBridge::StartMonitoring()
    {
        m_monitoring = true;
        if (m_eve) m_eve->StartMonitoring();
    }

    void HardwareBridge::StopMonitoring()
    {
        m_monitoring = false;
        if (m_eve) m_eve->StopMonitoring();
    }

    void HardwareBridge::SetAllLightsOff(bool off)
    {
        if (m_fxhl) m_fxhl->SetAllOff(off);
    }

    void HardwareBridge::SetDimmed(bool dimmed)
    {
        if (m_fxhl) m_fxhl->SetDimmed(dimmed);
    }

    void HardwareBridge::SetEffectsEnabled(bool enabled)
    {
        if (m_fxhl) m_fxhl->SetEffectsEnabled(enabled);
    }

    void HardwareBridge::SetFanCurve(int32_t fanId, std::vector<std::pair<int32_t, int32_t>> const& points)
    {
        if (!m_conf) return;

        // ConfigHandler has no direct SetFanCurve method; fan curves are managed
        // through ConfigFan + ACPI BIOS calls in the Win32 subsystem.
        // Log the operation and persist via ConfigBridge for now.
        wchar_t msg[256];
        swprintf_s(msg, L"Setting fan curve with %zu points for fan %d\n", points.size(), fanId);
        OutputDebugStringW(msg);

        // Persist the curve via ConfigBridge (separate temp/speed arrays).
        auto temps = winrt::single_threaded_vector<int32_t>();
        auto speeds = winrt::single_threaded_vector<int32_t>();
        for (auto const& [temp, speed] : points) {
            temps.Append(temp);
            speeds.Append(speed);
        }
        ConfigBridge::Instance().SaveFanCurve(fanId, temps.GetView(), speeds.GetView());
    }

    void HardwareBridge::SetPowerMode(int32_t mode)
    {
        if (m_conf) m_conf->SetPowerMode(mode);
    }

    void HardwareBridge::DetectDevices()
    {
        if (m_fxhl) m_fxhl->DetectDevices();
    }
}
