#pragma once
#include "HapticsPage.g.h"
#include "ViewModel/HapticsViewModel.h"

namespace winrt::AlienFX::implementation
{
    struct HapticsPage : HapticsPageT<HapticsPage>
    {
        HapticsPage();
        void AddGroupBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RemoveGroupBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::AlienFX::ViewModel::HapticsViewModel ViewModel() { return m_viewModel; }
        winrt::AlienFX::ViewModel::HapticsViewModel m_viewModel{ nullptr };
    };
}
namespace winrt::AlienFX::factory_implementation { struct HapticsPage : HapticsPageT<HapticsPage, implementation::HapticsPage> {}; }
