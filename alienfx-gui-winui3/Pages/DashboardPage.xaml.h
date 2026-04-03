#pragma once
#include "DashboardPage.g.h"

namespace winrt::AlienFX::implementation
{
    struct DashboardPage : DashboardPageT<DashboardPage>
    {
        DashboardPage();
    };
}

namespace winrt::AlienFX::factory_implementation
{
    struct DashboardPage : DashboardPageT<DashboardPage, implementation::DashboardPage> {};
}
