#include "pch.h"
#include "Helpers/ConfigBridge.h"
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Data.Json.h>

using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Foundation::Collections;
using namespace Windows::Data::Json;

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

    void ConfigBridge::SaveProfile(hstring const& name, IPropertySet const& data)
    {
        auto local = ApplicationData::Current().LocalSettings();
        auto key = L"Profile_" + name;

        // Serialize IPropertySet to JSON
        JsonObject json;
        for (auto const& pair : data) {
            auto k = pair.Key();
            auto v = pair.Value();
            if (auto s = v.try_as<hstring>()) {
                json.SetNamedValue(k, JsonValue::CreateStringValue(*s));
            }
            else if (auto b = v.try_as<bool>()) {
                json.SetNamedValue(k, JsonValue::CreateBooleanValue(*b));
            }
            else if (auto i = v.try_as<int32_t>()) {
                json.SetNamedValue(k, JsonValue::CreateNumberValue(*i));
            }
            else if (auto d = v.try_as<double>()) {
                json.SetNamedValue(k, JsonValue::CreateNumberValue(*d));
            }
        }

        local.Values().Insert(key, winrt::box_value(json.Stringify()));
    }

    IPropertySet ConfigBridge::LoadProfile(hstring const& name)
    {
        auto local = ApplicationData::Current().LocalSettings();
        auto key = L"Profile_" + name;

        if (auto val = local.Values().TryLookup(key)) {
            auto jsonStr = winrt::unbox_value<hstring>(val);
            auto json = JsonObject::Parse(jsonStr);

            auto result = single_threaded_observable_map<hstring, IInspectable>();
            for (auto const& pair : json) {
                auto k = pair.Key();
                auto v = pair.Value();
                if (v.ValueType() == JsonValueType::String) {
                    result.Insert(k, winrt::box_value(v.GetString()));
                }
                else if (v.ValueType() == JsonValueType::Boolean) {
                    result.Insert(k, winrt::box_value(v.GetBoolean()));
                }
                else if (v.ValueType() == JsonValueType::Number) {
                    result.Insert(k, winrt::box_value((int32_t)v.GetNumber()));
                }
            }
            return result;
        }
        return nullptr;
    }

    IVector<hstring> ConfigBridge::GetProfileNames()
    {
        auto local = ApplicationData::Current().LocalSettings();
        auto names = single_threaded_vector<hstring>();
        auto prefix = L"Profile_";

        for (auto const& pair : local.Values()) {
            auto key = pair.Key();
            if (key.size() >= prefix.size() && key.substr(0, prefix.size()) == prefix) {
                names.Append(key.substr(prefix.size()));
            }
        }
        return names;
    }

    void ConfigBridge::SaveFanCurve(int32_t fanId, IVector<int32_t> const& temps, IVector<int32_t> const& speeds)
    {
        auto local = ApplicationData::Current().LocalSettings();
        auto key = L"FanCurve_" + winrt::to_hstring(fanId);

        JsonObject json;
        JsonArray tempArr, speedArr;
        for (auto t : temps) {
            tempArr.Append(JsonValue::CreateNumberValue(t));
        }
        for (auto s : speeds) {
            speedArr.Append(JsonValue::CreateNumberValue(s));
        }
        json.SetNamedValue(L"temps", tempArr);
        json.SetNamedValue(L"speeds", speedArr);

        local.Values().Insert(key, winrt::box_value(json.Stringify()));
    }

    void ConfigBridge::LoadFanCurve(int32_t fanId, IVector<int32_t>& temps, IVector<int32_t>& speeds)
    {
        auto local = ApplicationData::Current().LocalSettings();
        auto key = L"FanCurve_" + winrt::to_hstring(fanId);

        if (auto val = local.Values().TryLookup(key)) {
            auto jsonStr = winrt::unbox_value<hstring>(val);
            auto json = JsonObject::Parse(jsonStr);

            temps.Clear();
            speeds.Clear();

            if (json.HasKey(L"temps")) {
                for (auto const& v : json.GetNamedArray(L"temps")) {
                    temps.Append((int32_t)v.GetNumber());
                }
            }
            if (json.HasKey(L"speeds")) {
                for (auto const& v : json.GetNamedArray(L"speeds")) {
                    speeds.Append((int32_t)v.GetNumber());
                }
            }
        }
    }

    void ConfigBridge::SaveHotkeys(hstring const& keys) { SaveSetting(L"hotkeys", keys); }
    hstring ConfigBridge::LoadHotkeys() { return LoadSetting(L"hotkeys", L""); }

    void ConfigBridge::ResetToDefaults()
    {
        auto local = ApplicationData::Current().LocalSettings();
        local.Values().Clear();
    }
}
