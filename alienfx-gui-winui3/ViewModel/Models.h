#pragma once
#include <winrt/Windows.Foundation.h>
#include <string>

namespace winrt::AlienFX::Model
{
    struct DeviceItem
    {
        int32_t Id{ 0 };
        hstring Name{ L"" };
        uint16_t VendorId{ 0 };
        uint16_t ProductId{ 0 };
        bool Connected{ false };
        hstring FirmwareVersion{ L"" };
    };

    struct LightItem
    {
        int32_t Id{ 0 };
        hstring Name{ L"" };
        int32_t Zone{ 0 };
        winrt::Windows::UI::Color CurrentColor{ 0, 0, 0, 255 };
    };

    struct ProfileItem
    {
        hstring Name{ L"" };
        bool IsDefault{ false };
        bool IsDimmed{ false };
        int32_t TriggerType{ 0 };
        hstring TriggerApp{ L"" };
        hstring TriggerKeys{ L"" };
    };

    struct SensorItem
    {
        hstring Name{ L"" };
        double Value{ 0.0 };
        hstring Unit{ L"" };
        int32_t Type{ 0 };
    };
}
