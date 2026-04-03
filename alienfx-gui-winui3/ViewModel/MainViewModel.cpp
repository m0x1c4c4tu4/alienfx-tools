#include "pch.h"
#include "ViewModel/MainViewModel.h"
#include "Helpers/HardwareBridge.h"

using namespace winrt;
using namespace Windows::Foundation::Collections;

namespace winrt::AlienFX::ViewModel::implementation
{
    MainViewModel::MainViewModel()
    {
        m_devices = single_threaded_observable_vector<Model::DeviceItem>();
    }

    hstring MainViewModel::PageTitle() { return m_pageTitle; }
    void MainViewModel::PageTitle(hstring const& value) { SetAndNotify(m_pageTitle, value, L"PageTitle"); }

    bool MainViewModel::LightsOn() { return m_lightsOn; }
    void MainViewModel::LightsOn(bool value) { SetAndNotify(m_lightsOn, value, L"LightsOn"); }

    bool MainViewModel::LightsDimmed() { return m_lightsDimmed; }
    void MainViewModel::LightsDimmed(bool value) { SetAndNotify(m_lightsDimmed, value, L"LightsDimmed"); }

    bool MainViewModel::EffectsEnabled() { return m_effectsEnabled; }
    void MainViewModel::EffectsEnabled(bool value) { SetAndNotify(m_effectsEnabled, value, L"EffectsEnabled"); }

    IObservableVector<Model::DeviceItem> MainViewModel::Devices() { return m_devices; }

    void MainViewModel::ToggleLights()
    {
        LightsOn(!m_lightsOn);
        HardwareBridge::Instance().SetAllLightsOff(!m_lightsOn);
    }
    void MainViewModel::ToggleDimmed()
    {
        LightsDimmed(!m_lightsDimmed);
        HardwareBridge::Instance().SetDimmed(!m_lightsDimmed);
    }
    void MainViewModel::ToggleEffects()
    {
        EffectsEnabled(!m_effectsEnabled);
        HardwareBridge::Instance().SetEffectsEnabled(!m_effectsEnabled);
    }
}
