#pragma once
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.h>

namespace winrt::AlienFX::Converters::implementation
{
    struct BoolToVisibilityConverter : implements<BoolToVisibilityConverter,
        Microsoft::UI::Xaml::Data::IValueConverter>
    {
        winrt::Windows::Foundation::IInspectable Convert(
            winrt::Windows::Foundation::IInspectable const& value,
            winrt::Windows::RuntimeType const& targetType,
            winrt::Windows::Foundation::IInspectable const& parameter,
            hstring const& language);

        winrt::Windows::Foundation::IInspectable ConvertBack(
            winrt::Windows::Foundation::IInspectable const& value,
            winrt::Windows::RuntimeType const& targetType,
            winrt::Windows::Foundation::IInspectable const& parameter,
            hstring const& language);
    };
}
