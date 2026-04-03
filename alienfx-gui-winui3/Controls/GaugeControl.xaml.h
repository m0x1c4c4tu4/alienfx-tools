#pragma once
#include "GaugeControl.g.h"
#include <winrt/Windows.UI.h>
namespace winrt::AlienFX::Controls::implementation
{
    struct GaugeControl : GaugeControlT<GaugeControl>
    {
        GaugeControl();
        void SetValue(double value);
        void SetRange(double min, double max);
        void SetLabel(hstring const& label);
        void UpdateDisplay();
    private:
        double m_value{ 0 }, m_min{ 0 }, m_max{ 100 };
        hstring m_label{ L"Gauge" };
        void DrawArc(double percentage);
    };
}
namespace winrt::AlienFX::Controls::factory_implementation
{
    struct GaugeControl : GaugeControlT<GaugeControl, implementation::GaugeControl> {};
}
