#include "pch.h"
#include "AmbientPage.xaml.h"

namespace winrt::AlienFX::implementation
{
    AmbientPage::AmbientPage()
    {
        InitializeComponent();
        m_viewModel = this->DataContext().as<winrt::AlienFX::ViewModel::AmbientViewModel>();
    }

    void AmbientPage::AddZone_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().AddZone();
    }

    void AmbientPage::RemoveZone_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().RemoveZone();
    }

    void AmbientPage::ResetAmbient_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().Reset();
    }
}
