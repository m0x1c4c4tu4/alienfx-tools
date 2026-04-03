#pragma once
#include "ViewModel/ViewModelBase.h"
#include "ViewModel/Models.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.h>
#include <cstdint>

namespace winrt::AlienFX::ViewModel::implementation
{
    struct ColorsViewModel : ViewModelBase
    {
    public:
        ColorsViewModel();

        int32_t EffectType();
        void EffectType(int32_t value);

        int32_t ColorMode();
        void ColorMode(int32_t value);

        int32_t Tempo();
        void Tempo(int32_t value);

        int32_t Length();
        void Length(int32_t value);

        winrt::Windows::UI::Color SelectedColor();
        void SelectedColor(winrt::Windows::UI::Color const& value);

        bool Circle();
        void Circle(bool value);
        bool Random();
        void Random(bool value);
        bool Phase();
        void Phase(bool value);
        bool Background();
        void Background(bool value);
        bool ReversePos();
        void ReversePos(bool value);
        bool Spectrum();
        void Spectrum(bool value);
        bool Reverse();
        void Reverse(bool value);

        struct EffectEntry { hstring Name; int32_t Type; winrt::Windows::UI::Color Color; };
        winrt::Windows::Foundation::Collections::IObservableVector<EffectEntry> Effects();

        void AddEffect();
        void RemoveEffect();
        void ApplyEffect();

    private:
        int32_t m_effectType{ 0 };
        int32_t m_colorMode{ 0 };
        int32_t m_tempo{ 500 };
        int32_t m_length{ 10 };
        winrt::Windows::UI::Color m_selectedColor{ 0, 212, 170, 255 };
        bool m_circle{ false }, m_random{ false }, m_phase{ false };
        bool m_background{ false }, m_reversePos{ false }, m_spectrum{ false }, m_reverse{ false };
        winrt::Windows::Foundation::Collections::IObservableVector<EffectEntry> m_effects{ nullptr };
    };
}
