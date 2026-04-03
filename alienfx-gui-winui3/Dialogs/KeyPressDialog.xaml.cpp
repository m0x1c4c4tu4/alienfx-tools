#include "pch.h"
#include "KeyPressDialog.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Input.h>
using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Input;
namespace winrt::AlienFX::Dialogs::implementation
{
    KeyPressDialog::KeyPressDialog() { InitializeComponent(); }
    void KeyPressDialog::KeyCaptureArea_KeyDown(IInspectable const&, KeyRoutedEventArgs const& args)
    {
        if (auto txt = FindName(L"CapturedKeyText").try_as<Controls::TextBlock>()) {
            hstring keyName = args.Key().ToString();
            txt.Text(keyName);
        }
        if (auto txt = FindName(L"ScanCodeText").try_as<Controls::TextBlock>()) {
            txt.Text(hstring{L"VirtualKey: "} + to_hstring((int32_t)args.Key()));
        }
    }
    hstring KeyPressDialog::GetCapturedKey() { return m_capturedKey; }
    int32_t KeyPressDialog::GetScanCode() { return m_scanCode; }
}
