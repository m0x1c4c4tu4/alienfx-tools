#include "pch.h"
#include "HapticsPage.xaml.h"

namespace winrt::AlienFX::implementation
{
    HapticsPage::HapticsPage()
    {
        InitializeComponent();
        m_viewModel = this->DataContext().as<winrt::AlienFX::ViewModel::HapticsViewModel>();
    }

    void HapticsPage::AddGroupBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().AddGroup();
    }

    void HapticsPage::RemoveGroupBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().RemoveGroup();
    }
}
