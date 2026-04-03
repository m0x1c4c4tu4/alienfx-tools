#pragma once
#include "ViewModel/ViewModelBase.h"
#include "ViewModel/Models.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.h>

namespace winrt::AlienFX::ViewModel::implementation
{
    struct LightingViewModel : ViewModelBase
    {
    public:
        LightingViewModel();

        int32_t SelectedDevice();
        void SelectedDevice(int32_t value);

        int32_t SelectedZone();
        void SelectedZone(int32_t value);

        hstring SelectedLightName();
        void SelectedLightName(hstring const& value);

        winrt::Windows::UI::Color SelectedColor();
        void SelectedColor(winrt::Windows::UI::Color const& value);

        bool LightsOn();
        void LightsOn(bool value);

        bool LightsDimmed();
        void LightsDimmed(bool value);

        bool EffectsEnabled();
        void EffectsEnabled(bool value);

        winrt::Windows::Foundation::Collections::IObservableVector<Model::DeviceItem> Devices();
        winrt::Windows::Foundation::Collections::IObservableVector<Model::LightItem> Lights();

        void ApplyColor();
        void TestColor();
        void ToggleLights();
        void ToggleDimmed();
        void ToggleEffects();

    private:
        int32_t m_selectedDevice{ 0 };
        int32_t m_selectedZone{ 0 };
        hstring m_selectedLightName{ L"" };
        winrt::Windows::UI::Color m_selectedColor{ 0, 212, 170, 255 };
        bool m_lightsOn{ true };
        bool m_lightsDimmed{ false };
        bool m_effectsEnabled{ true };
        winrt::Windows::Foundation::Collections::IObservableVector<Model::DeviceItem> m_devices{ nullptr };
        winrt::Windows::Foundation::Collections::IObservableVector<Model::LightItem> m_lights{ nullptr };
    };
}
