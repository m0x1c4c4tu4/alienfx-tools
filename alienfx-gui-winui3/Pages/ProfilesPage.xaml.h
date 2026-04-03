#pragma once
#include "ProfilesPage.g.h"
namespace winrt::AlienFX::implementation { struct ProfilesPage : ProfilesPageT<ProfilesPage> { ProfilesPage(); }; }
namespace winrt::AlienFX::factory_implementation { struct ProfilesPage : ProfilesPageT<ProfilesPage, implementation::ProfilesPage> {}; }
