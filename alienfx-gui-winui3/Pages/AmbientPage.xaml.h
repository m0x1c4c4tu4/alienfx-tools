#pragma once
#include "AmbientPage.g.h"
namespace winrt::AlienFX::implementation { struct AmbientPage : AmbientPageT<AmbientPage> { AmbientPage(); }; }
namespace winrt::AlienFX::factory_implementation { struct AmbientPage : AmbientPageT<AmbientPage, implementation::AmbientPage> {}; }
