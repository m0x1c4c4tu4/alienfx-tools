#pragma once
#include "ViewModel/ViewModelBase.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <cstdint>
namespace winrt::AlienFX::ViewModel::implementation {
    struct EventsViewModel : ViewModelBase {
    public:
        EventsViewModel();
        int32_t EventSource(); void EventSource(int32_t v);
        int32_t CutLevel(); void CutLevel(int32_t v);
        bool NoEventColor(); void NoEventColor(bool v);
        bool EventBackground(); void EventBackground(bool v);
        bool EventPriority(); void EventPriority(bool v);
        struct EventEntry { hstring Source; int32_t Level; winrt::Windows::UI::Color Color; };
        winrt::Windows::Foundation::Collections::IObservableVector<EventEntry> Events();
        void AddEvent(); void RemoveEvent(); void MoveUp(); void MoveDown(); void ApplyEvents();
    private:
        int32_t m_eventSource{ 0 }, m_cutLevel{ 50 };
        bool m_noEventColor{ false }, m_eventBackground{ false }, m_eventPriority{ false };
        winrt::Windows::Foundation::Collections::IObservableVector<EventEntry> m_events{ nullptr };
    };
    struct AmbientViewModel : ViewModelBase {
    public:
        AmbientViewModel();
        int32_t HScale(); void HScale(int32_t v);
        int32_t VScale(); void VScale(int32_t v);
        int32_t DisplayFreq(); void DisplayFreq(int32_t v);
        bool Spectrum(); void Spectrum(bool v);
        bool Reverse(); void Reverse(bool v);
        struct ZoneEntry { hstring Name; winrt::Windows::UI::Color Color; };
        winrt::Windows::Foundation::Collections::IObservableVector<ZoneEntry> Zones();
        void AddZone(); void RemoveZone(); void Reset(); void ApplyAmbient();
    private:
        int32_t m_hScale{ 50 }, m_vScale{ 50 }, m_displayFreq{ 2 };
        bool m_spectrum{ false }, m_reverse{ false };
        winrt::Windows::Foundation::Collections::IObservableVector<ZoneEntry> m_zones{ nullptr };
    };
    struct HapticsViewModel : ViewModelBase {
    public:
        HapticsViewModel();
        int32_t Tact(); void Tact(int32_t v);
        int32_t Width(); void Width(int32_t v);
        bool Circle(); void Circle(bool v);
        bool Random(); void Random(bool v);
        bool Phase(); void Phase(bool v);
        bool Background(); void Background(bool v);
        bool ReversePos(); void ReversePos(bool v);
        bool Spectrum(); void Spectrum(bool v);
        struct FreqGroup { hstring Name; hstring Range; };
        winrt::Windows::Foundation::Collections::IObservableVector<FreqGroup> Groups();
        void AddGroup(); void RemoveGroup(); void ApplyHaptics();
    private:
        int32_t m_tact{ 500 }, m_width{ 10 };
        bool m_circle{ false }, m_random{ false }, m_phase{ false };
        bool m_background{ false }, m_reversePos{ false }, m_spectrum{ false };
        winrt::Windows::Foundation::Collections::IObservableVector<FreqGroup> m_groups{ nullptr };
    };
    struct GridViewModel : ViewModelBase {
    public:
        GridViewModel();
        int32_t EffectType(); void EffectType(int32_t v);
        int32_t Speed(); void Speed(int32_t v);
        int32_t Width(); void Width(int32_t v);
        int32_t Tact(); void Tact(int32_t v);
        int32_t Trigger(); void Trigger(int32_t v);
        bool Circle(); void Circle(bool v);
        bool Random(); void Random(bool v);
        bool Phase(); void Phase(bool v);
        struct ColorPhase { hstring Name; winrt::Windows::UI::Color Color; };
        winrt::Windows::Foundation::Collections::IObservableVector<ColorPhase> Colors();
        void AddColor(); void RemoveColor(); void ClearGrid(); void ApplyGrid();
    private:
        int32_t m_effectType{ 0 }, m_speed{ 500 }, m_width{ 10 }, m_tact{ 500 }, m_trigger{ 0 };
        bool m_circle{ false }, m_random{ false }, m_phase{ false };
        winrt::Windows::Foundation::Collections::IObservableVector<ColorPhase> m_colors{ nullptr };
    };
    struct DevicesViewModel : ViewModelBase {
    public:
        DevicesViewModel();
        hstring LightName(); void LightName(hstring const& v);
        bool ShowGridNames(); void ShowGridNames(bool v);
        hstring DeviceInfo(); void DeviceInfo(hstring const& v);
        struct FoundDevice { hstring Name; hstring VidPid; bool Connected; };
        winrt::Windows::Foundation::Collections::IObservableVector<Model::DeviceItem> Devices();
        winrt::Windows::Foundation::Collections::IObservableVector<hstring> Zones();
        winrt::Windows::Foundation::Collections::IObservableVector<FoundDevice> FoundDevices();
        void Detect(); void LoadMap(); void SaveMap(); void WhiteBalance(); void ClearLight();
        void AddZone(); void DeleteZone(); void SelectFromList();
    private:
        hstring m_lightName{ L"" }, m_deviceInfo{ L"" };
        bool m_showGridNames{ false };
        winrt::Windows::Foundation::Collections::IObservableVector<Model::DeviceItem> m_devices{ nullptr };
        winrt::Windows::Foundation::Collections::IObservableVector<hstring> m_zones{ nullptr };
        winrt::Windows::Foundation::Collections::IObservableVector<FoundDevice> m_found{ nullptr };
    };
    struct FansViewModel : ViewModelBase {
    public:
        FansViewModel();
        int32_t PowerMode(); void PowerMode(int32_t v);
        int32_t ACBoost(); void ACBoost(int32_t v);
        int32_t DCBoost(); void DCBoost(int32_t v);
        int32_t TCC(); void TCC(int32_t v);
        int32_t XMP(); void XMP(int32_t v);
        struct SensorData { hstring Name; double Value; hstring Unit; };
        struct FanData { hstring Name; int32_t Speed; };
        struct CurvePoint { int32_t Temp; int32_t Speed; };
        winrt::Windows::Foundation::Collections::IObservableVector<SensorData> Sensors();
        winrt::Windows::Foundation::Collections::IObservableVector<FanData> Fans();
        winrt::Windows::Foundation::Collections::IObservableVector<CurvePoint> CurvePoints();
        void ApplyCurve(); void ResetCurve(); void EnableOverboost(); void ResetBoost();
    private:
        int32_t m_powerMode{ 0 }, m_acBoost{ 0 }, m_dcBoost{ 0 }, m_tcc{ 50 }, m_xmp{ 50 };
        winrt::Windows::Foundation::Collections::IObservableVector<SensorData> m_sensors{ nullptr };
        winrt::Windows::Foundation::Collections::IObservableVector<FanData> m_fans{ nullptr };
        winrt::Windows::Foundation::Collections::IObservableVector<CurvePoint> m_curve{ nullptr };
    };
    struct ProfilesViewModel : ViewModelBase {
    public:
        ProfilesViewModel();
        hstring ProfileName(); void ProfileName(hstring const& v);
        int32_t TriggerType(); void TriggerType(int32_t v);
        hstring TriggerApp(); void TriggerApp(hstring const& v);
        hstring TriggerKeys(); void TriggerKeys(hstring const& v);
        hstring ScriptName(); void ScriptName(hstring const& v);
        bool DefaultProfile(); void DefaultProfile(bool v);
        bool PriorityProfile(); void PriorityProfile(bool v);
        bool ProfileDim(); void ProfileDim(bool v);
        bool ForegroundProfile(); void ForegroundProfile(bool v);
        bool RunScript(); void RunScript(bool v);
        bool FanProfile(); void FanProfile(bool v);
        struct ProfileEntry { hstring Name; hstring Trigger; bool IsDefault; };
        struct DeviceEffect { hstring Device; hstring Effect; };
        winrt::Windows::Foundation::Collections::IObservableVector<ProfileEntry> Profiles();
        winrt::Windows::Foundation::Collections::IObservableVector<DeviceEffect> DeviceEffects();
        void AddProfile(); void RemoveProfile(); void CopyActive(); void Reset(); void ConfigureEffects();
    private:
        hstring m_profileName{ L"" }, m_triggerApp{ L"" }, m_triggerKeys{ L"" }, m_scriptName{ L"" };
        int32_t m_triggerType{ 0 };
        bool m_defaultProfile{ false }, m_priorityProfile{ false }, m_profileDim{ false };
        bool m_foregroundProfile{ false }, m_runScript{ false }, m_fanProfile{ false };
        winrt::Windows::Foundation::Collections::IObservableVector<ProfileEntry> m_profiles{ nullptr };
        winrt::Windows::Foundation::Collections::IObservableVector<DeviceEffect> m_deviceEffects{ nullptr };
    };
    struct SettingsViewModel : ViewModelBase {
    public:
        SettingsViewModel();
        bool StartWithWindows(); void StartWithWindows(bool v);
        bool StartMinimized(); void StartMinimized(bool v);
        int32_t DimmingPower(); void DimmingPower(int32_t v);
        bool PowerDim(); void PowerDim(bool v);
        bool OffPowerButton(); void OffPowerButton(bool v);
        bool ScreenOff(); void ScreenOff(bool v);
        bool BatDim(); void BatDim(bool v);
        bool OffOnBattery(); void OffOnBattery(bool v);
        bool EnableEffects(); void EnableEffects(bool v);
        bool LightsOn(); void LightsOn(bool v);
        bool GammaCorrection(); void GammaCorrection(bool v);
        bool EffectsOnBattery(); void EffectsOnBattery(bool v);
        int32_t PollingRate(); void PollingRate(int32_t v);
        bool FanControl(); void FanControl(bool v);
        bool DisableAWCC(); void DisableAWCC(bool v);
        bool ESIFTemp(); void ESIFTemp(bool v);
        bool KeepSystem(); void KeepSystem(bool v);
        bool BatFan(); void BatFan(bool v);
        bool DiskSensors(); void DiskSensors(bool v);
        bool OverclockEnable(); void OverclockEnable(bool v);
        bool NumlockActive(); void NumlockActive(bool v);
        bool ActionLights(); void ActionLights(bool v);
        bool PowerButton(); void PowerButton(bool v);
        bool Indicator(); void Indicator(bool v);
        bool NoDesktop(); void NoDesktop(bool v);
        bool ResetOnWake(); void ResetOnWake(bool v);
        bool UpdateCheck(); void UpdateCheck(bool v);
        void ConfigureHotkeys(); void CheckForUpdates(); void SaveSettings(); void LoadSettings();
    private:
        bool m_startWithWindows{ false }, m_startMinimized{ false };
        int32_t m_dimmingPower{ 50 };
        bool m_powerDim{ false }, m_offPowerButton{ false }, m_screenOff{ false };
        bool m_batDim{ false }, m_offOnBattery{ false };
        bool m_enableEffects{ true }, m_lightsOn{ true }, m_gammaCorrection{ false };
        bool m_effectsOnBattery{ false };
        int32_t m_pollingRate{ 100 };
        bool m_fanControl{ false }, m_disableAWCC{ false }, m_esifTemp{ false };
        bool m_keepSystem{ false }, m_batFan{ false }, m_diskSensors{ false };
        bool m_overclockEnable{ false }, m_numlockActive{ false }, m_actionLights{ false };
        bool m_powerButton{ false }, m_indicator{ false }, m_noDesktop{ false }, m_resetOnWake{ false };
        bool m_updateCheck{ true };
    };
}
