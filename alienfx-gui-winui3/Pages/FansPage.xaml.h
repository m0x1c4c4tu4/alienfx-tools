#pragma once
#include "FansPage.g.h"
#include "ViewModel/AllViewModels.h"

namespace winrt::AlienFX::implementation
{
    struct FansPage : FansPageT<FansPage>
    {
    public:
        FansPage();

        void ApplyCurve_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void ResetCurve_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void EnableOverboost_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void ResetBoost_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        ViewModel::implementation::FansViewModel m_vm;
    };
}
namespace winrt::AlienFX::factory_implementation { struct FansPage : FansPageT<FansPage, implementation::FansPage> {}; }
