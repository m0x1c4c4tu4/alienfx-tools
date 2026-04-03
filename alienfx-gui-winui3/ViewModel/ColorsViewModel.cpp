#include "pch.h"
#include "ViewModel/ColorsViewModel.h"
#include "Helpers/HardwareBridge.h"
using namespace winrt;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
namespace winrt::AlienFX::ViewModel::implementation {
    ColorsViewModel::ColorsViewModel() { m_effects = single_threaded_observable_vector<EffectEntry>(); }
    int32_t ColorsViewModel::EffectType() { return m_effectType; }
    void ColorsViewModel::EffectType(int32_t v) { SetAndNotify(m_effectType, v, L"EffectType"); }
    int32_t ColorsViewModel::ColorMode() { return m_colorMode; }
    void ColorsViewModel::ColorMode(int32_t v) { SetAndNotify(m_colorMode, v, L"ColorMode"); }
    int32_t ColorsViewModel::Tempo() { return m_tempo; }
    void ColorsViewModel::Tempo(int32_t v) { SetAndNotify(m_tempo, v, L"Tempo"); }
    int32_t ColorsViewModel::Length() { return m_length; }
    void ColorsViewModel::Length(int32_t v) { SetAndNotify(m_length, v, L"Length"); }
    Color ColorsViewModel::SelectedColor() { return m_selectedColor; }
    void ColorsViewModel::SelectedColor(Color const& v) { SetAndNotify(m_selectedColor, v, L"SelectedColor"); }
    bool ColorsViewModel::Circle() { return m_circle; }
    void ColorsViewModel::Circle(bool v) { SetAndNotify(m_circle, v, L"Circle"); }
    bool ColorsViewModel::Random() { return m_random; }
    void ColorsViewModel::Random(bool v) { SetAndNotify(m_random, v, L"Random"); }
    bool ColorsViewModel::Phase() { return m_phase; }
    void ColorsViewModel::Phase(bool v) { SetAndNotify(m_phase, v, L"Phase"); }
    bool ColorsViewModel::Background() { return m_background; }
    void ColorsViewModel::Background(bool v) { SetAndNotify(m_background, v, L"Background"); }
    bool ColorsViewModel::ReversePos() { return m_reversePos; }
    void ColorsViewModel::ReversePos(bool v) { SetAndNotify(m_reversePos, v, L"ReversePos"); }
    bool ColorsViewModel::Spectrum() { return m_spectrum; }
    void ColorsViewModel::Spectrum(bool v) { SetAndNotify(m_spectrum, v, L"Spectrum"); }
    bool ColorsViewModel::Reverse() { return m_reverse; }
    void ColorsViewModel::Reverse(bool v) { SetAndNotify(m_reverse, v, L"Reverse"); }
    IObservableVector<EffectEntry> ColorsViewModel::Effects() { return m_effects; }
    void ColorsViewModel::AddEffect() { m_effects.Append(EffectEntry{ L"New Effect", m_effectType, m_selectedColor }); OnPropertyChanged(L"Effects"); }
    void ColorsViewModel::RemoveEffect() { if (m_effects.Size() > 0) { m_effects.RemoveAt(m_effects.Size() - 1); OnPropertyChanged(L"Effects"); } }
    void ColorsViewModel::ApplyEffect() { Helpers::HardwareBridge::Instance().UpdateGlobalEffectAsync(0, m_effectType); }
}
