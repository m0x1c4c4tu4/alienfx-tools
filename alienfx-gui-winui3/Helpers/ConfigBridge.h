#pragma once
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>
#include <string>

namespace winrt::AlienFX::Helpers
{
    struct ConfigBridge
    {
        static ConfigBridge& Instance();

        void Initialize();

        void SaveSetting(hstring const& key, hstring const& value);
        hstring LoadSetting(hstring const& key, hstring const& defaultValue);

        void SaveBool(hstring const& key, bool value);
        bool LoadBool(hstring const& key, bool defaultValue);

        void SaveInt(hstring const& key, int32_t value);
        int32_t LoadInt(hstring const& key, int32_t defaultValue);

        void SaveProfile(hstring const& name, winrt::Windows::Foundation::Collections::IPropertySet const& data);
        winrt::Windows::Foundation::Collections::IPropertySet LoadProfile(hstring const& name);
        winrt::Windows::Foundation::Collections::IVector<hstring> GetProfileNames();

        void SaveFanCurve(int32_t fanId, winrt::Windows::Foundation::Collections::IVector<int32_t> const& temps, winrt::Windows::Foundation::Collections::IVector<int32_t> const& speeds);
        void LoadFanCurve(int32_t fanId, winrt::Windows::Foundation::Collections::IVector<int32_t>& temps, winrt::Windows::Foundation::Collections::IVector<int32_t>& speeds);

        void SaveHotkeys(hstring const& keys);
        hstring LoadHotkeys();

        void ResetToDefaults();

    private:
        ConfigBridge() = default;
        hstring m_settingsPath{ L"" };
        hstring m_profilesPath{ L"" };
    };
}
