#pragma once
#include "EventsPage.g.h"
#include "ViewModel/EventsViewModel.h"

namespace winrt::AlienFX::implementation
{
    struct EventsPage : EventsPageT<EventsPage>
    {
        EventsPage();
        void AddEventBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RemoveEventBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void MoveUpBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void MoveDownBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::AlienFX::ViewModel::EventsViewModel ViewModel() { return m_viewModel; }
        winrt::AlienFX::ViewModel::EventsViewModel m_viewModel{ nullptr };
    };
}
namespace winrt::AlienFX::factory_implementation { struct EventsPage : EventsPageT<EventsPage, implementation::EventsPage> {}; }
