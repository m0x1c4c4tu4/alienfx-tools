#include "pch.h"
#include "FreqBarsControl.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Shapes;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;

namespace winrt::AlienFX::Controls::implementation
{
    FreqBarsControl::FreqBarsControl() { InitializeComponent(); }

    void FreqBarsControl::UpdateBars(winrt::Windows::Foundation::Collections::IVector<double> const& values)
    {
        if (auto repeater = FindName(L"BarsRepeater").try_as<Controls::ItemsRepeater>()) {
            repeater.ItemsSource(values);
        }
    }

    void FreqBarsControl::SetBarCount(int32_t count)
    {
        m_barCount = count;
    }
}
