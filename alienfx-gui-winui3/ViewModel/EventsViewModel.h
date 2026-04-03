#pragma once
#include "ViewModel/ViewModelBase.h"
#include "ViewModel/Models.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.h>
#include <cstdint>

namespace winrt::AlienFX::ViewModel::implementation
{
    struct EventsViewModel : ViewModelBase
    {
    public:
        EventsViewModel();

        int32_t EventSource();
        void EventSource(int32_t value);

        int32_t CutLevel();
        void CutLevel(int32_t value);

        winrt::Windows::UI::Color SelectedColor();
        void SelectedColor(winrt::Windows::UI::Color const& value);

        bool NoEventColor();
        void NoEventColor(bool value);
        bool EventBackground();
        void EventBackground(bool value);
        bool EventPriority();
        void EventPriority(bool value);

        struct EventEntry { hstring Source; int32_t Level; winrt::Windows::UI::Color Color; };
        winrt::Windows::Foundation::Collections::IObservableVector<EventEntry> Events();

        void AddEvent();
        void RemoveEvent();
        void MoveUp();
        void MoveDown();
        void ApplyEvents();

    private:
        int32_t m_eventSource{ 0 }, m_cutLevel{ 50 };
        winrt::Windows::UI::Color m_selectedColor{ 0, 212, 170, 255 };
        bool m_noEventColor{ false }, m_eventBackground{ false }, m_eventPriority{ false };
        winrt::Windows::Foundation::Collections::IObservableVector<EventEntry> m_events{ nullptr };
    };
}
