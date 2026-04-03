#pragma once
#include "HapticsPage.g.h"
namespace winrt::AlienFX::implementation { struct HapticsPage : HapticsPageT<HapticsPage> { HapticsPage(); }; }
namespace winrt::AlienFX::factory_implementation { struct HapticsPage : HapticsPageT<HapticsPage, implementation::HapticsPage> {}; }
