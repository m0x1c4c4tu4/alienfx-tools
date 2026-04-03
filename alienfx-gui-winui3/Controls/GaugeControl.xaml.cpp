#include "pch.h"
#include "GaugeControl.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <cmath>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Shapes;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;

namespace winrt::AlienFX::Controls::implementation
{
    GaugeControl::GaugeControl() { InitializeComponent(); UpdateDisplay(); }

    void GaugeControl::SetValue(double value) { m_value = value; UpdateDisplay(); }
    void GaugeControl::SetRange(double min, double max) { m_min = min; m_max = max; UpdateDisplay(); }
    void GaugeControl::SetLabel(hstring const& label) { m_label = label; UpdateDisplay(); }

    void GaugeControl::UpdateDisplay()
    {
        if (auto text = FindName(L"ValueText").try_as<Controls::TextBlock>())
            text.Text(to_hstring(std::lround(m_value)));
        if (auto label = FindName(L"Label").try_as<Controls::TextBlock>())
            label.Text(m_label);
        if (auto minmax = FindName(L"MinMaxText").try_as<Controls::TextBlock>())
            minmax.Text(hstring{ L"Min: " } + to_hstring(std::lround(m_min)) + L" | Max: " + to_hstring(std::lround(m_max)));
        double pct = (m_max != m_min) ? (m_value - m_min) / (m_max - m_min) : 0;
        DrawArc(pct);
    }

    void GaugeControl::DrawArc(double pct)
    {
        if (auto canvas = FindName(L"GaugeBackground").try_as<Shapes::Path>()) {
            double angle = pct * 270.0;
            double rad = angle * 3.14159 / 180.0;
            double x = 50 + 40 * std::cos(rad - 3.14159 * 0.75);
            double y = 50 + 40 * std::sin(rad - 3.14159 * 0.75);
            int largeArc = (angle > 180) ? 1 : 0;
            hstring data = L"M 15 65 A 40 40 0 " + to_hstring(largeArc) + L" 1 " + to_hstring(x) + L" " + to_hstring(y);
            canvas.Data(winrt::Microsoft::UI::Xaml::Media::GeometryHelper::Parse(data));
        }
    }
}
