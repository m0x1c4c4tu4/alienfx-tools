#include "pch.h"
#include "ColorButton.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::AlienFX::Controls::implementation
{
    ColorButton::ColorButton() { InitializeComponent(); }

    Windows::UI::Color ColorButton::SelectedColor() { return m_color; }
    void ColorButton::SelectedColor(Windows::UI::Color const& value) { m_color = value; UpdatePreview(); m_colorChanged(*this, value); }

    event_token ColorButton::SelectedColorChanged(TypedEventHandler<Controls::ColorButton, Windows::UI::Color> const& handler) { return m_colorChanged.add(handler); }
    void ColorButton::SelectedColorChanged(event_token const& token) noexcept { m_colorChanged.remove(token); }

    void ColorButton::ColorBtn_Click(IInspectable const&, RoutedEventArgs const&) { ColorBtn().Flyout().ShowAt(ColorBtn()); }
    void ColorButton::Picker_ColorChanged(ColorPicker const& sender, ColorChangedEventArgs const&) { SelectedColor(sender.Color()); }
    void ColorButton::UpdatePreview()
    {
        if (auto rect = FindName(L"ColorPreview").try_as<Shapes::Rectangle>())
        {
            rect.Fill(Media::SolidColorBrush{ m_color });
        }
        if (auto text = FindName(L"HexText").try_as<Controls::TextBlock>())
        {
            wchar_t hex[8];
            swprintf_s(hex, L"#%02X%02X%02X", m_color.R, m_color.G, m_color.B);
            text.Text(hex);
        }
    }
}
