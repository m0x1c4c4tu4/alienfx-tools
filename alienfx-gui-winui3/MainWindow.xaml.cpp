#include "pch.h"
#include "MainWindow.xaml.h"
#include "Pages/LightingPage.xaml.h"
#include "Pages/FansPage.xaml.h"
#include "Pages/ProfilesPage.xaml.h"
#include "Pages/SettingsPage.xaml.h"
#include "Pages/DashboardPage.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;

namespace winrt::AlienFX::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
    }

    void MainWindow::NavView_SelectionChanged(NavigationView const& sender,
        NavigationViewSelectionChangedEventArgs const& args)
    {
        if (auto item = args.SelectedItem().try_as<NavigationViewItem>())
        {
            if (auto tag = item.Tag().try_as<hstring>())
            {
                NavigateToPage(tag.value());
            }
        }
    }

    void MainWindow::NavigateToPage(hstring const& tag)
    {
        auto frame = ContentFrame();
        hstring pageType;

        if (tag == L"dashboard")
        {
            frame.Navigate(xaml_typename<AlienFX::DashboardPage>());
        }
        else if (tag == L"colors" || tag == L"lighting")
        {
            frame.Navigate(xaml_typename<AlienFX::LightingPage>());
        }
        else if (tag == L"fans")
        {
            frame.Navigate(xaml_typename<AlienFX::FansPage>());
        }
        else if (tag == L"profiles")
        {
            frame.Navigate(xaml_typename<AlienFX::ProfilesPage>());
        }
        else if (tag == L"settings")
        {
            frame.Navigate(xaml_typename<AlienFX::SettingsPage>());
        }
        else if (tag == L"about")
        {
            ContentDialog about;
            about.Title(box_value(L"About AlienFX Control"));
            about.Content(box_value(L"AlienFX Control - WinUI 3\n\nAlienware hardware lighting and fan control."));
            about.CloseButtonText(L"OK");
            about.XamlRoot(Content().XamlRoot());
            about.ShowAsync();
        }
    }
}
