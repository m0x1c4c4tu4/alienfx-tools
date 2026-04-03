#pragma once
#include "FansPage.g.h"
namespace winrt::AlienFX::implementation { struct FansPage : FansPageT<FansPage> { FansPage(); }; }
namespace winrt::AlienFX::factory_implementation { struct FansPage : FansPageT<FansPage, implementation::FansPage> {}; }
