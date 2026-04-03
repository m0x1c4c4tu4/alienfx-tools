#include "pch.h"
#include "ColorsPage.xaml.h"

namespace winrt::AlienFX::implementation
{
    ColorsPage::ColorsPage()
    {
        InitializeComponent();
        m_viewModel = this->DataContext().as<winrt::AlienFX::ViewModel::ColorsViewModel>();
    }

    void ColorsPage::AddEffectBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().AddEffect();
    }

    void ColorsPage::RemoveEffectBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().RemoveEffect();
    }

    void ColorsPage::TestColorBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().ApplyEffect();
    }
}
