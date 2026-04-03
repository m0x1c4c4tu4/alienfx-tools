#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Composition::SystemBackdrops;

namespace winrt::AlienFX::implementation
{
    App::App()
    {
        InitializeComponent();
    }

    void App::OnLaunched(LaunchActivatedEventArgs const&)
    {
        m_window = make<MainWindow>();
        m_window.Activate();

        // Apply Mica backdrop
        auto windowNative = m_window.as<Microsoft::UI::IWindowNative>();
        HWND hwnd{ nullptr };
        windowNative.get_WindowHandle(&hwnd);

        if (MicaController::IsSupported())
        {
            Microsoft::UI::Xaml::Media::MicaBackdrop mica;
            mica.Kind(Microsoft::UI::Xaml::Media::MicaKind::BaseAlt);
            if (auto backdrop = m_window.as<Microsoft::UI::ICompositionSupportsSystemBackdrop>())
            {
                // Mica set via XAML or code-behind on MainWindow
            }
        }
    }
}
