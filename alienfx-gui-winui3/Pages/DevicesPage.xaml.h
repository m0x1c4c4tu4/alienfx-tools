#pragma once
#include "DevicesPage.g.h"
#include "ViewModel/AllViewModels.h"

namespace winrt::AlienFX::implementation
{
    struct DevicesPage : DevicesPageT<DevicesPage>
    {
    public:
        DevicesPage();

        ViewModel::DevicesViewModel ViewModel();

        void OnDetect(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OnLoadMap(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OnSaveMap(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OnAddZone(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OnDeleteZone(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OnSelectFromList(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OnWhiteBalance(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OnClearLight(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        ViewModel::DevicesViewModel m_viewModel{ nullptr };
    };
}

namespace winrt::AlienFX::factory_implementation
{
    struct DevicesPage : DevicesPageT<DevicesPage, implementation::DevicesPage>
    {
    };
}
