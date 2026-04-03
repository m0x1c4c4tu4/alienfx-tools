#pragma once
#include "ProfilesPage.g.h"
#include "ViewModel/AllViewModels.h"

namespace winrt::AlienFX::implementation
{
    struct ProfilesPage : ProfilesPageT<ProfilesPage>
    {
    public:
        ProfilesPage();

        void AddProfile_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void RemoveProfile_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void CopyActive_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void Reset_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void ConfigureEffects_Click(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        ViewModel::implementation::ProfilesViewModel m_vm;
    };
}
namespace winrt::AlienFX::factory_implementation { struct ProfilesPage : ProfilesPageT<ProfilesPage, implementation::ProfilesPage> {}; }
