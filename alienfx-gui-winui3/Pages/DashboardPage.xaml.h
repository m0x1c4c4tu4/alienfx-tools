#pragma once
#include "DashboardPage.g.h"
#include "ViewModel/MainViewModel.h"
#include "Helpers/HardwareBridge.h"
#include <winrt/Windows.Foundation.Collections.h>

namespace winrt::AlienFX::implementation
{
    struct DashboardPage : DashboardPageT<DashboardPage>
    {
        DashboardPage();

        void ToggleLightsBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ToggleDimmedBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ToggleEffectsBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        winrt::Windows::Foundation::Collections::IObservableVector<Model::SensorItem> Sensors();
        int32_t DeviceCount();
        hstring SensorSummary();

    private:
        winrt::AlienFX::ViewModel::MainViewModel ViewModel() { return m_viewModel; }
        winrt::AlienFX::ViewModel::MainViewModel m_viewModel{ nullptr };
        winrt::Windows::Foundation::Collections::IObservableVector<Model::SensorItem> m_sensors{ nullptr };
    };
}

namespace winrt::AlienFX::factory_implementation
{
    struct DashboardPage : DashboardPageT<DashboardPage, implementation::DashboardPage> {};
}
