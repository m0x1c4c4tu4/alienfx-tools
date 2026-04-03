#pragma once
#include "ColorButton.g.h"
#include <winrt/Windows.UI.h>

namespace winrt::AlienFX::Controls::implementation
{
    struct ColorButton : ColorButtonT<ColorButton>
    {
        ColorButton();
        Windows::UI::Color SelectedColor();
        void SelectedColor(Windows::UI::Color const& value);
        event_token SelectedColorChanged(TypedEventHandler<Controls::ColorButton, Windows::UI::Color> const& handler);
        void SelectedColorChanged(event_token const& token) noexcept;

    private:
        void ColorBtn_Click(IInspectable const&, RoutedEventArgs const&);
        void Picker_ColorChanged(Microsoft::UI::Xaml::Controls::ColorPicker const&, Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const&);
        void UpdatePreview();

        Windows::UI::Color m_color{ 0, 0, 0, 255 };
        event<TypedEventHandler<Controls::ColorButton, Windows::UI::Color>> m_colorChanged;
    };
}

namespace winrt::AlienFX::Controls::factory_implementation
{
    struct ColorButton : ColorButtonT<ColorButton, implementation::ColorButton> {};
}
