#pragma once
#include "LedGridControl.g.h"
#include <winrt/Windows.Foundation.Collections.h>

namespace winrt::AlienFX::Controls::implementation
{
    struct LedGridControl : LedGridControlT<LedGridControl>
    {
        LedGridControl();
        void Cell_Tapped(IInspectable const&, Input::TappedRoutedEventArgs const&);
    };
}

namespace winrt::AlienFX::Controls::factory_implementation
{
    struct LedGridControl : LedGridControlT<LedGridControl, implementation::LedGridControl> {};
}
