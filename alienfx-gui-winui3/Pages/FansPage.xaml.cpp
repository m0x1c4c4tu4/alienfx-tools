#include "pch.h"
#include "FansPage.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::AlienFX::implementation
{
    FansPage::FansPage()
    {
        InitializeComponent();
        DataContext(m_vm);
    }

    void FansPage::ApplyCurve_Click(IInspectable const&, RoutedEventArgs const&)
    {
        m_vm.ApplyCurve();
    }

    void FansPage::ResetCurve_Click(IInspectable const&, RoutedEventArgs const&)
    {
        m_vm.ResetCurve();
    }

    void FansPage::EnableOverboost_Click(IInspectable const&, RoutedEventArgs const&)
    {
        m_vm.EnableOverboost();
    }

    void FansPage::ResetBoost_Click(IInspectable const&, RoutedEventArgs const&)
    {
        m_vm.ResetBoost();
    }
}
