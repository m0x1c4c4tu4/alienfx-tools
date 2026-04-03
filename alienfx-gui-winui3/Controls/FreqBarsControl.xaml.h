#pragma once
#include "FreqBarsControl.g.h"
namespace winrt::AlienFX::Controls::implementation { struct FreqBarsControl : FreqBarsControlT<FreqBarsControl> { FreqBarsControl(); }; }
namespace winrt::AlienFX::Controls::factory_implementation { struct FreqBarsControl : FreqBarsControlT<FreqBarsControl, implementation::FreqBarsControl> {}; }
