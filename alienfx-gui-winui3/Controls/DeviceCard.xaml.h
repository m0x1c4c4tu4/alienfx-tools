#pragma once
#include "DeviceCard.g.h"
namespace winrt::AlienFX::Controls::implementation { struct DeviceCard : DeviceCardT<DeviceCard> { DeviceCard(); }; }
namespace winrt::AlienFX::Controls::factory_implementation { struct DeviceCard : DeviceCardT<DeviceCard, implementation::DeviceCard> {}; }
