#include "pch.h"
#include "LedGridControl.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Input;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;

namespace winrt::AlienFX::Controls::implementation
{
    LedGridControl::LedGridControl() { InitializeComponent(); }

    void LedGridControl::Cell_Tapped(IInspectable const& sender, TappedRoutedEventArgs const&)
    {
        if (auto border = sender.try_as<Shapes::Border>()) {
            border.Background(SolidColorBrush{ Color{255,0,212,170} });
        }
    }

    void LedGridControl::SetGridData(winrt::Windows::Foundation::Collections::IVector<hstring> const& labels,
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Color> const& colors)
    {
        if (auto repeater = FindName(L"GridItems").try_as<Controls::ItemsRepeater>()) {
            repeater.ItemsSource(labels);
        }
    }

    void LedGridControl::HighlightCell(int32_t row, int32_t col, winrt::Windows::UI::Color color)
    {
        (void)row; (void)col; (void)color;
    }

    void LedGridControl::ClearHighlights() {}
}
