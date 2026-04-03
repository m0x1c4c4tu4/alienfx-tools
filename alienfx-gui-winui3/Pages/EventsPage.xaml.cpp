#include "pch.h"
#include "EventsPage.xaml.h"

namespace winrt::AlienFX::implementation
{
    EventsPage::EventsPage()
    {
        InitializeComponent();
        m_viewModel = this->DataContext().as<winrt::AlienFX::ViewModel::EventsViewModel>();
    }

    void EventsPage::AddEventBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().AddEvent();
    }

    void EventsPage::RemoveEventBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().RemoveEvent();
    }

    void EventsPage::MoveUpBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().MoveUp();
    }

    void EventsPage::MoveDownBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().MoveDown();
    }
}
