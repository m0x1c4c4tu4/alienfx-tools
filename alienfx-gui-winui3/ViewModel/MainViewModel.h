#pragma once
#include "ViewModel/ViewModelBase.h"
#include "ViewModel/Models.h"
#include <winrt/Windows.Foundation.Collections.h>

namespace winrt::AlienFX::ViewModel::implementation
{
    struct MainViewModel : ViewModelBase
    {
    public:
        MainViewModel();

        hstring PageTitle();
        void PageTitle(hstring const& value);

        bool LightsOn();
        void LightsOn(bool value);

        bool LightsDimmed();
        void LightsDimmed(bool value);

        bool EffectsEnabled();
        void EffectsEnabled(bool value);

        winrt::Windows::Foundation::Collections::IObservableVector<Model::DeviceItem> Devices();

        void ToggleLights();
        void ToggleDimmed();
        void ToggleEffects();

    private:
        hstring m_pageTitle{ L"Dashboard" };
        bool m_lightsOn{ true };
        bool m_lightsDimmed{ false };
        bool m_effectsEnabled{ true };
        winrt::Windows::Foundation::Collections::IObservableVector<Model::DeviceItem> m_devices{ nullptr };
    };
}
