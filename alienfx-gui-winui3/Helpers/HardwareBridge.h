#pragma once
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.h>
#include <cstdint>
#include <vector>

class ConfigHandler;
class FXHelper;
class EventHandler;

namespace winrt::AlienFX::Helpers
{
    struct SensorData
    {
        hstring Name;
        double Value;
        hstring Unit;
    };

    struct HardwareBridge
    {
        static HardwareBridge& Instance();

        void Initialize(ConfigHandler* conf, FXHelper* fxhl, EventHandler* eve);

        winrt::Windows::Foundation::IAsyncAction SetLightAsync(
            int32_t deviceId, int32_t lightId, winrt::Windows::UI::Color color);

        winrt::Windows::Foundation::IAsyncAction UpdateGlobalEffectAsync(
            int32_t deviceId, int32_t effectType);

        winrt::Windows::Foundation::Collections::IVectorView<int32_t> GetDevices();

        winrt::Windows::Foundation::Collections::IVectorView<SensorData> GetSensors();

        event<winrt::Windows::Foundation::TypedEventHandler<HardwareBridge, SensorData>> SensorUpdated;

        void StartMonitoring();
        void StopMonitoring();

        void SetAllLightsOff(bool off);
        void SetDimmed(bool dimmed);
        void SetEffectsEnabled(bool enabled);
        void SetFanCurve(int32_t fanId, std::vector<std::pair<int32_t, int32_t>> const& points);
        void SetPowerMode(int32_t mode);
        void DetectDevices();

    private:
        HardwareBridge() = default;
        ConfigHandler* m_conf{ nullptr };
        FXHelper* m_fxhl{ nullptr };
        EventHandler* m_eve{ nullptr };
        bool m_monitoring{ false };
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<HardwareBridge, SensorData>> m_sensorUpdated;
    };
}
