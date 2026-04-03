#include "pch.h"
#include "Helpers/ConfigBridge.h"
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.Collections.h>

using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Foundation::Collections;

namespace winrt::AlienFX::Helpers
{
    ConfigBridge& ConfigBridge::Instance()
    {
        static ConfigBridge instance;
        return instance;
    }

    void ConfigBridge::Initialize()
    {
        auto local = ApplicationData::Current().LocalSettings();
        m_settingsPath = local.Values().TryLookup(L"path").try_as<hstring>().value_or(L"");
        m_profilesPath = L"profiles";
    }

    void ConfigBridge::SaveSetting(hstring const& key, hstring const& value)
    {
        auto local = ApplicationData::Current().LocalSettings();
        local.Values().Insert(key, winrt::box_value(value));
    }

    hstring ConfigBridge::LoadSetting(hstring const& key, hstring const& defaultValue)
    {
        auto local = ApplicationData::Current().LocalSettings();
        if (auto val = local.Values().TryLookup(key)) {
            return winrt::unbox_value<hstring>(val);
        }
        return defaultValue;
    }

    void ConfigBridge::SaveBool(hstring const& key, bool value)
    {
        auto local = ApplicationData::Current().LocalSettings();
        local.Values().Insert(key, winrt::box_value(value));
    }

    bool ConfigBridge::LoadBool(hstring const& key, bool defaultValue)
    {
        auto local = ApplicationData::Current().LocalSettings();
        if (auto val = local.Values().TryLookup(key)) {
            return winrt::unbox_value<bool>(val);
        }
        return defaultValue;
    }

    void ConfigBridge::SaveInt(hstring const& key, int32_t value)
    {
        auto local = ApplicationData::Current().LocalSettings();
        local.Values().Insert(key, winrt::box_value(value));
    }

    int32_t ConfigBridge::LoadInt(hstring const& key, int32_t defaultValue)
    {
        auto local = ApplicationData::Current().LocalSettings();
        if (auto val = local.Values().TryLookup(key)) {
            return winrt::unbox_value<int32_t>(val);
        }
        return defaultValue;
    }

    void ConfigBridge::SaveProfile(hstring const&, IPropertySet const&) {}
    IPropertySet ConfigBridge::LoadProfile(hstring const&) { return nullptr; }
    IVector<hstring> ConfigBridge::GetProfileNames() { return single_threaded_vector<hstring>({}); }

    void ConfigBridge::SaveFanCurve(int32_t, IVector<int32_t> const&, IVector<int32_t> const&) {}
    void ConfigBridge::LoadFanCurve(int32_t, IVector<int32_t>&, IVector<int32_t>&) {}

    void ConfigBridge::SaveHotkeys(hstring const& keys) { SaveSetting(L"hotkeys", keys); }
    hstring ConfigBridge::LoadHotkeys() { return LoadSetting(L"hotkeys", L""); }

    void ConfigBridge::ResetToDefaults()
    {
        auto local = ApplicationData::Current().LocalSettings();
        local.Values().Clear();
    }
}
