#pragma once
#include "EventsPage.g.h"
namespace winrt::AlienFX::implementation { struct EventsPage : EventsPageT<EventsPage> { EventsPage(); }; }
namespace winrt::AlienFX::factory_implementation { struct EventsPage : EventsPageT<EventsPage, implementation::EventsPage> {}; }
