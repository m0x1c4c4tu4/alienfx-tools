#include "pch.h"
#include "GridPage.xaml.h"

namespace winrt::AlienFX::implementation
{
    GridPage::GridPage()
    {
        InitializeComponent();
        m_viewModel = this->DataContext().as<winrt::AlienFX::ViewModel::GridViewModel>();
    }

    void GridPage::AddColorBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().AddColor();
    }

    void GridPage::RemoveColorBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().RemoveColor();
    }

    void GridPage::ClearGridBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().ClearGrid();
    }
}
