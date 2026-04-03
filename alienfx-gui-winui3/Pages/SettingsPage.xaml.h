#pragma once
#include "SettingsPage.g.h"
namespace winrt::AlienFX::implementation { struct SettingsPage : SettingsPageT<SettingsPage> { SettingsPage(); }; }
namespace winrt::AlienFX::factory_implementation { struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage> {}; }
