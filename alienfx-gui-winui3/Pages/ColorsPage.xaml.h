#pragma once
#include "ColorsPage.g.h"
#include "ViewModel/ColorsViewModel.h"

namespace winrt::AlienFX::implementation
{
    struct ColorsPage : ColorsPageT<ColorsPage>
    {
        ColorsPage();
        void AddEffectBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RemoveEffectBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TestColorBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::AlienFX::ViewModel::ColorsViewModel ViewModel() { return m_viewModel; }
        winrt::AlienFX::ViewModel::ColorsViewModel m_viewModel{ nullptr };
    };
}
namespace winrt::AlienFX::factory_implementation { struct ColorsPage : ColorsPageT<ColorsPage, implementation::ColorsPage> {}; }
