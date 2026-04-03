#pragma once
#include "AmbientPage.g.h"
#include "ViewModel/AmbientViewModel.h"

namespace winrt::AlienFX::implementation
{
    struct AmbientPage : AmbientPageT<AmbientPage>
    {
        AmbientPage();
        void AddZone_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RemoveZone_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ResetAmbient_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::AlienFX::ViewModel::AmbientViewModel ViewModel() { return m_viewModel; }
        winrt::AlienFX::ViewModel::AmbientViewModel m_viewModel{ nullptr };
    };
}
namespace winrt::AlienFX::factory_implementation { struct AmbientPage : AmbientPageT<AmbientPage, implementation::AmbientPage> {}; }
