#pragma once
#include "ColorsPage.g.h"
namespace winrt::AlienFX::implementation { struct ColorsPage : ColorsPageT<ColorsPage> { ColorsPage(); }; }
namespace winrt::AlienFX::factory_implementation { struct ColorsPage : ColorsPageT<ColorsPage, implementation::ColorsPage> {}; }
