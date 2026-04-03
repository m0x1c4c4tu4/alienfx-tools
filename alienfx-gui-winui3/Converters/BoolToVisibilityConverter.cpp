#include "pch.h"
#include "Converters/BoolToVisibilityConverter.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Data;

namespace winrt::AlienFX::Converters::implementation
{
    IInspectable BoolToVisibilityConverter::Convert(
        IInspectable const& value, Windows::RuntimeType const&,
        IInspectable const& parameter, hstring const&)
    {
        if (auto b = value.try_as<bool>())
        {
            auto invert = parameter.try_as<hstring>() && parameter.as<hstring>() == L"Inverse";
            bool result = invert ? !b.value() : b.value();
            return box_value(result ? Visibility::Visible : Visibility::Collapsed);
        }
        return box_value(Visibility::Collapsed);
    }

    IInspectable BoolToVisibilityConverter::ConvertBack(
        IInspectable const& value, Windows::RuntimeType const&,
        IInspectable const&, hstring const&)
    {
        if (auto v = value.try_as<Visibility>())
        {
            return box_value(v.value() == Visibility::Visible);
        }
        return box_value(false);
    }
}
