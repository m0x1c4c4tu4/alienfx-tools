#include "pch.h"
#include "WhiteBalanceDialog.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Media.h>
using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;
namespace winrt::AlienFX::Dialogs::implementation
{
    WhiteBalanceDialog::WhiteBalanceDialog() { InitializeComponent(); }
    void WhiteBalanceDialog::UpdatePreview()
    {
        if (auto border = FindName(L"ColorPreview").try_as<Controls::Border>()) {
            Color c{ 255,
                (uint8_t)RedSlider().Value(),
                (uint8_t)GreenSlider().Value(),
                (uint8_t)BlueSlider().Value() };
            border.Background(SolidColorBrush{ c });
        }
    }
    Windows::UI::Color WhiteBalanceDialog::GetColor()
    {
        return { 255, (uint8_t)RedSlider().Value(), (uint8_t)GreenSlider().Value(), (uint8_t)BlueSlider().Value() };
    }
}
