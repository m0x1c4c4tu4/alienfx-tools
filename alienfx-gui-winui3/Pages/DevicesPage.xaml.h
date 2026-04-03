#pragma once
#include "DevicesPage.g.h"
namespace winrt::AlienFX::implementation { struct DevicesPage : DevicesPageT<DevicesPage> { DevicesPage(); }; }
namespace winrt::AlienFX::factory_implementation { struct DevicesPage : DevicesPageT<DevicesPage, implementation::DevicesPage> {}; }
