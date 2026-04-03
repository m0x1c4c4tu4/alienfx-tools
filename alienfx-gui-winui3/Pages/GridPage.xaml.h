#pragma once
#include "GridPage.g.h"
#include "ViewModel/AllViewModels.h"

namespace winrt::AlienFX::implementation
{
    struct GridPage : GridPageT<GridPage>
    {
        GridPage();
        void AddColorBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RemoveColorBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ClearGridBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::AlienFX::ViewModel::GridViewModel ViewModel() { return m_viewModel; }
        winrt::AlienFX::ViewModel::GridViewModel m_viewModel{ nullptr };
    };
}
namespace winrt::AlienFX::factory_implementation { struct GridPage : GridPageT<GridPage, implementation::GridPage> {}; }
