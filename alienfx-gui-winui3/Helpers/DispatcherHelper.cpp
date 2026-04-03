#include "pch.h"
#include "Helpers/DispatcherHelper.h"

using namespace winrt;
using namespace Microsoft::UI::Dispatching;

namespace winrt::AlienFX::Helpers
{
    DispatcherQueue DispatcherHelper::m_dispatcher{ nullptr };

    void DispatcherHelper::SetDispatcher(DispatcherQueue const& dispatcher)
    {
        m_dispatcher = dispatcher;
    }

    DispatcherQueue DispatcherHelper::GetDispatcher()
    {
        return m_dispatcher;
    }

    void DispatcherHelper::RunAsync(std::function<void()> const& action)
    {
        if (m_dispatcher)
        {
            m_dispatcher.TryEnqueue([action]()
            {
                action();
                return true;
            });
        }
    }
}
