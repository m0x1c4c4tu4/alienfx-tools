#pragma once
#include "MainWindow.g.h"
#include <winrt/Microsoft.UI.Xaml.Controls.h>

namespace winrt::AlienFX::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void NavView_SelectionChanged(Microsoft::UI::Xaml::Controls::NavigationView const& sender,
            Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);

    private:
        void NavigateToPage(hstring const& tag);
    };
}

namespace winrt::AlienFX::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow> {};
}
