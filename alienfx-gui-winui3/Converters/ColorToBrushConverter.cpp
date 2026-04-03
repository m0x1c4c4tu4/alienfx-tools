#include "pch.h"
#include "Converters/ColorToBrushConverter.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml::Data;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;

namespace winrt::AlienFX::Converters::implementation
{
    IInspectable ColorToBrushConverter::Convert(
        IInspectable const& value, Windows::RuntimeType const&,
        IInspectable const&, hstring const&)
    {
        if (auto color = value.try_as<Color>())
        {
            return SolidColorBrush{ color.value() };
        }
        return DependencyProperty::UnsetValue();
    }

    IInspectable ColorToBrushConverter::ConvertBack(
        IInspectable const&, Windows::RuntimeType const&,
        IInspectable const&, hstring const&)
    {
        throw hresult_not_implemented{ L"ConvertBack not supported" };
    }
}
