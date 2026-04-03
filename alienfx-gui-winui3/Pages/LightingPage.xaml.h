#pragma once
#include "LightingPage.g.h"
namespace winrt::AlienFX::implementation { struct LightingPage : LightingPageT<LightingPage> { LightingPage(); }; }
namespace winrt::AlienFX::factory_implementation { struct LightingPage : LightingPageT<LightingPage, implementation::LightingPage> {}; }
