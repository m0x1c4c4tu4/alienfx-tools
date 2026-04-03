#include "pch.h"
#include "ViewModel/LightingViewModel.h"
#include "Helpers/HardwareBridge.h"

using namespace winrt;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;

namespace winrt::AlienFX::ViewModel::implementation
{
    LightingViewModel::LightingViewModel()
    {
        m_devices = single_threaded_observable_vector<Model::DeviceItem>();
        m_lights = single_threaded_observable_vector<Model::LightItem>();
    }

    int32_t LightingViewModel::SelectedDevice() { return m_selectedDevice; }
    void LightingViewModel::SelectedDevice(int32_t value) { SetAndNotify(m_selectedDevice, value, L"SelectedDevice"); }

    int32_t LightingViewModel::SelectedZone() { return m_selectedZone; }
    void LightingViewModel::SelectedZone(int32_t value) { SetAndNotify(m_selectedZone, value, L"SelectedZone"); }

    hstring LightingViewModel::SelectedLightName() { return m_selectedLightName; }
    void LightingViewModel::SelectedLightName(hstring const& value) { SetAndNotify(m_selectedLightName, value, L"SelectedLightName"); }

    Color LightingViewModel::SelectedColor() { return m_selectedColor; }
    void LightingViewModel::SelectedColor(Color const& value) { SetAndNotify(m_selectedColor, value, L"SelectedColor"); }

    bool LightingViewModel::LightsOn() { return m_lightsOn; }
    void LightingViewModel::LightsOn(bool value) { SetAndNotify(m_lightsOn, value, L"LightsOn"); }

    bool LightingViewModel::LightsDimmed() { return m_lightsDimmed; }
    void LightingViewModel::LightsDimmed(bool value) { SetAndNotify(m_lightsDimmed, value, L"LightsDimmed"); }

    bool LightingViewModel::EffectsEnabled() { return m_effectsEnabled; }
    void LightingViewModel::EffectsEnabled(bool value) { SetAndNotify(m_effectsEnabled, value, L"EffectsEnabled"); }

    IObservableVector<Model::DeviceItem> LightingViewModel::Devices() { return m_devices; }
    IObservableVector<Model::LightItem> LightingViewModel::Lights() { return m_lights; }

    void LightingViewModel::ApplyColor()
    {
        auto& bridge = Helpers::HardwareBridge::Instance();
        bridge.SetLightAsync(m_selectedDevice, m_selectedZone, m_selectedColor);
    }

    void LightingViewModel::TestColor()
    {
        auto& bridge = Helpers::HardwareBridge::Instance();
        bridge.SetLightAsync(m_selectedDevice, m_selectedZone, m_selectedColor);
    }

    void LightingViewModel::ToggleLights() { LightsOn(!m_lightsOn); }
    void LightingViewModel::ToggleDimmed() { LightsDimmed(!m_lightsDimmed); }
    void LightingViewModel::ToggleEffects() { EffectsEnabled(!m_effectsEnabled); }
}
