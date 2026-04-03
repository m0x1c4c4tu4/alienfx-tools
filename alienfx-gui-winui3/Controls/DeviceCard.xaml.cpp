#include "pch.h"
#include "DeviceCard.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Media.h>
using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;
namespace winrt::AlienFX::Controls::implementation
{
    DeviceCard::DeviceCard() { InitializeComponent(); }
    void DeviceCard::SetDeviceInfo(hstring const& name, hstring const& vidPid, bool connected)
    {
        if (auto txt = FindName(L"DeviceName").try_as<Controls::TextBlock>()) txt.Text(name);
        if (auto txt = FindName(L"VidPid").try_as<Controls::TextBlock>()) txt.Text(vidPid);
        if (auto dot = FindName(L"StatusDot").try_as<Shapes::Ellipse>())
            dot.Fill(SolidColorBrush{ connected ? Color{255,0,212,170} : Color{255,128,128,128} });
    }
    void DeviceCard::SetFirmware(hstring const& version)
    {
        if (auto txt = FindName(L"FirmwareVersion").try_as<Controls::TextBlock>())
            txt.Text(hstring{L"Firmware: "} + version);
    }
}
