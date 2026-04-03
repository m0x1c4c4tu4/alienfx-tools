#include "pch.h"
#include "ProfilesPage.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::AlienFX::implementation
{
    ProfilesPage::ProfilesPage()
    {
        InitializeComponent();
        DataContext(m_vm);
    }

    void ProfilesPage::AddProfile_Click(IInspectable const&, RoutedEventArgs const&)
    {
        m_vm.AddProfile();
    }

    void ProfilesPage::RemoveProfile_Click(IInspectable const&, RoutedEventArgs const&)
    {
        m_vm.RemoveProfile();
    }

    void ProfilesPage::CopyActive_Click(IInspectable const&, RoutedEventArgs const&)
    {
        m_vm.CopyActive();
    }

    void ProfilesPage::Reset_Click(IInspectable const&, RoutedEventArgs const&)
    {
        m_vm.Reset();
    }

    void ProfilesPage::ConfigureEffects_Click(IInspectable const&, RoutedEventArgs const&)
    {
        m_vm.ConfigureEffects();
    }
}
