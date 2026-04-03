#pragma once
#include "GridPage.g.h"
namespace winrt::AlienFX::implementation { struct GridPage : GridPageT<GridPage> { GridPage(); }; }
namespace winrt::AlienFX::factory_implementation { struct GridPage : GridPageT<GridPage, implementation::GridPage> {}; }
