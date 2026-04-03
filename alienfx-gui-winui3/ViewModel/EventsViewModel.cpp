#include "pch.h"
#include "ViewModel/EventsViewModel.h"
#include "Helpers/HardwareBridge.h"
using namespace winrt;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
namespace winrt::AlienFX::ViewModel::implementation {
    EventsViewModel::EventsViewModel() { m_events = single_threaded_observable_vector<EventEntry>(); }
    int32_t EventsViewModel::EventSource() { return m_eventSource; }
    void EventsViewModel::EventSource(int32_t v) { SetAndNotify(m_eventSource, v, L"EventSource"); }
    int32_t EventsViewModel::CutLevel() { return m_cutLevel; }
    void EventsViewModel::CutLevel(int32_t v) { SetAndNotify(m_cutLevel, v, L"CutLevel"); }
    Color EventsViewModel::SelectedColor() { return m_selectedColor; }
    void EventsViewModel::SelectedColor(Color const& v) { SetAndNotify(m_selectedColor, v, L"SelectedColor"); }
    bool EventsViewModel::NoEventColor() { return m_noEventColor; }
    void EventsViewModel::NoEventColor(bool v) { SetAndNotify(m_noEventColor, v, L"NoEventColor"); }
    bool EventsViewModel::EventBackground() { return m_eventBackground; }
    void EventsViewModel::EventBackground(bool v) { SetAndNotify(m_eventBackground, v, L"EventBackground"); }
    bool EventsViewModel::EventPriority() { return m_eventPriority; }
    void EventsViewModel::EventPriority(bool v) { SetAndNotify(m_eventPriority, v, L"EventPriority"); }
    IObservableVector<EventEntry> EventsViewModel::Events() { return m_events; }
    void EventsViewModel::AddEvent() { m_events.Append(EventEntry{ L"New Event", m_cutLevel, m_selectedColor }); OnPropertyChanged(L"Events"); }
    void EventsViewModel::RemoveEvent() { if (m_events.Size() > 0) { m_events.RemoveAt(m_events.Size() - 1); OnPropertyChanged(L"Events"); } }
    void EventsViewModel::MoveUp() { uint32_t idx = m_events.Size() - 1; if (idx > 0) { auto item = m_events.GetAt(idx); m_events.RemoveAt(idx); m_events.InsertAt(idx - 1, item); OnPropertyChanged(L"Events"); } }
    void EventsViewModel::MoveDown() { uint32_t idx = m_events.Size() - 1; if (idx + 1 < m_events.Size()) { auto item = m_events.GetAt(idx); m_events.RemoveAt(idx); m_events.InsertAt(idx + 1, item); OnPropertyChanged(L"Events"); } }
    void EventsViewModel::ApplyEvents() { Helpers::HardwareBridge::Instance().UpdateGlobalEffectAsync(0, m_eventSource); }
}
