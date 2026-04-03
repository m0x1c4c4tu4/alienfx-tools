#pragma once
#include <winrt/Microsoft.UI.Dispatching.h>

namespace winrt::AlienFX::Helpers
{
    struct DispatcherHelper
    {
        static void SetDispatcher(winrt::Microsoft::UI::Dispatching::DispatcherQueue const& dispatcher);
        static winrt::Microsoft::UI::Dispatching::DispatcherQueue GetDispatcher();
        static void RunAsync(std::function<void()> const& action);

    private:
        static winrt::Microsoft::UI::Dispatching::DispatcherQueue m_dispatcher;
    };
}
