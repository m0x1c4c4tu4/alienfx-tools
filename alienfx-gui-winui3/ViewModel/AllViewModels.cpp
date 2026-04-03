#include "pch.h"
#include "ViewModel/AllViewModels.h"
#include "Helpers/HardwareBridge.h"
using namespace winrt;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
namespace winrt::AlienFX::ViewModel::implementation {
// EventsViewModel
EventsViewModel::EventsViewModel() { m_events = single_threaded_observable_vector<EventEntry>(); }
int32_t EventsViewModel::EventSource() { return m_eventSource; }
void EventsViewModel::EventSource(int32_t v) { SetAndNotify(m_eventSource, v, L"EventSource"); }
int32_t EventsViewModel::CutLevel() { return m_cutLevel; }
void EventsViewModel::CutLevel(int32_t v) { SetAndNotify(m_cutLevel, v, L"CutLevel"); }
bool EventsViewModel::NoEventColor() { return m_noEventColor; }
void EventsViewModel::NoEventColor(bool v) { SetAndNotify(m_noEventColor, v, L"NoEventColor"); }
bool EventsViewModel::EventBackground() { return m_eventBackground; }
void EventsViewModel::EventBackground(bool v) { SetAndNotify(m_eventBackground, v, L"EventBackground"); }
bool EventsViewModel::EventPriority() { return m_eventPriority; }
void EventsViewModel::EventPriority(bool v) { SetAndNotify(m_eventPriority, v, L"EventPriority"); }
IObservableVector<EventEntry> EventsViewModel::Events() { return m_events; }
void EventsViewModel::AddEvent() { m_events.Append(EventEntry{ L"New Event", m_cutLevel, {0,212,170,255} }); OnPropertyChanged(L"Events"); }
void EventsViewModel::RemoveEvent() { if (m_events.Size() > 0) { m_events.RemoveAt(m_events.Size()-1); OnPropertyChanged(L"Events"); } }
void EventsViewModel::MoveUp() {}
void EventsViewModel::MoveDown() {}
void EventsViewModel::ApplyEvents() { Helpers::HardwareBridge::Instance().UpdateGlobalEffectAsync(0, 1); }

// AmbientViewModel
AmbientViewModel::AmbientViewModel() { m_zones = single_threaded_observable_vector<ZoneEntry>(); }
int32_t AmbientViewModel::HScale() { return m_hScale; }
void AmbientViewModel::HScale(int32_t v) { SetAndNotify(m_hScale, v, L"HScale"); }
int32_t AmbientViewModel::VScale() { return m_vScale; }
void AmbientViewModel::VScale(int32_t v) { SetAndNotify(m_vScale, v, L"VScale"); }
int32_t AmbientViewModel::DisplayFreq() { return m_displayFreq; }
void AmbientViewModel::DisplayFreq(int32_t v) { SetAndNotify(m_displayFreq, v, L"DisplayFreq"); }
bool AmbientViewModel::Spectrum() { return m_spectrum; }
void AmbientViewModel::Spectrum(bool v) { SetAndNotify(m_spectrum, v, L"Spectrum"); }
bool AmbientViewModel::Reverse() { return m_reverse; }
void AmbientViewModel::Reverse(bool v) { SetAndNotify(m_reverse, v, L"Reverse"); }
IObservableVector<ZoneEntry> AmbientViewModel::Zones() { return m_zones; }
void AmbientViewModel::AddZone() { m_zones.Append(ZoneEntry{ L"Zone " + to_hstring(m_zones.Size()+1), {0,212,170,255} }); OnPropertyChanged(L"Zones"); }
void AmbientViewModel::RemoveZone() { if (m_zones.Size() > 0) { m_zones.RemoveAt(m_zones.Size()-1); OnPropertyChanged(L"Zones"); } }
void AmbientViewModel::Reset() { m_zones.Clear(); OnPropertyChanged(L"Zones"); }
void AmbientViewModel::ApplyAmbient() { Helpers::HardwareBridge::Instance().UpdateGlobalEffectAsync(0, 2); }

// HapticsViewModel
HapticsViewModel::HapticsViewModel() { m_groups = single_threaded_observable_vector<FreqGroup>(); }
int32_t HapticsViewModel::Tact() { return m_tact; }
void HapticsViewModel::Tact(int32_t v) { SetAndNotify(m_tact, v, L"Tact"); }
int32_t HapticsViewModel::Width() { return m_width; }
void HapticsViewModel::Width(int32_t v) { SetAndNotify(m_width, v, L"Width"); }
bool HapticsViewModel::Circle() { return m_circle; }
void HapticsViewModel::Circle(bool v) { SetAndNotify(m_circle, v, L"Circle"); }
bool HapticsViewModel::Random() { return m_random; }
void HapticsViewModel::Random(bool v) { SetAndNotify(m_random, v, L"Random"); }
bool HapticsViewModel::Phase() { return m_phase; }
void HapticsViewModel::Phase(bool v) { SetAndNotify(m_phase, v, L"Phase"); }
bool HapticsViewModel::Background() { return m_background; }
void HapticsViewModel::Background(bool v) { SetAndNotify(m_background, v, L"Background"); }
bool HapticsViewModel::ReversePos() { return m_reversePos; }
void HapticsViewModel::ReversePos(bool v) { SetAndNotify(m_reversePos, v, L"ReversePos"); }
bool HapticsViewModel::Spectrum() { return m_spectrum; }
void HapticsViewModel::Spectrum(bool v) { SetAndNotify(m_spectrum, v, L"Spectrum"); }
IObservableVector<FreqGroup> HapticsViewModel::Groups() { return m_groups; }
void HapticsViewModel::AddGroup() { m_groups.Append(FreqGroup{ L"Group " + to_hstring(m_groups.Size()+1), L"20-20000Hz" }); OnPropertyChanged(L"Groups"); }
void HapticsViewModel::RemoveGroup() { if (m_groups.Size() > 0) { m_groups.RemoveAt(m_groups.Size()-1); OnPropertyChanged(L"Groups"); } }
void HapticsViewModel::ApplyHaptics() { Helpers::HardwareBridge::Instance().UpdateGlobalEffectAsync(0, 3); }

// GridViewModel
GridViewModel::GridViewModel() { m_colors = single_threaded_observable_vector<ColorPhase>(); }
int32_t GridViewModel::EffectType() { return m_effectType; }
void GridViewModel::EffectType(int32_t v) { SetAndNotify(m_effectType, v, L"EffectType"); }
int32_t GridViewModel::Speed() { return m_speed; }
void GridViewModel::Speed(int32_t v) { SetAndNotify(m_speed, v, L"Speed"); }
int32_t GridViewModel::Width() { return m_width; }
void GridViewModel::Width(int32_t v) { SetAndNotify(m_width, v, L"Width"); }
int32_t GridViewModel::Tact() { return m_tact; }
void GridViewModel::Tact(int32_t v) { SetAndNotify(m_tact, v, L"Tact"); }
int32_t GridViewModel::Trigger() { return m_trigger; }
void GridViewModel::Trigger(int32_t v) { SetAndNotify(m_trigger, v, L"Trigger"); }
bool GridViewModel::Circle() { return m_circle; }
void GridViewModel::Circle(bool v) { SetAndNotify(m_circle, v, L"Circle"); }
bool GridViewModel::Random() { return m_random; }
void GridViewModel::Random(bool v) { SetAndNotify(m_random, v, L"Random"); }
bool GridViewModel::Phase() { return m_phase; }
void GridViewModel::Phase(bool v) { SetAndNotify(m_phase, v, L"Phase"); }
IObservableVector<ColorPhase> GridViewModel::Colors() { return m_colors; }
void GridViewModel::AddColor() { m_colors.Append(ColorPhase{ L"Phase " + to_hstring(m_colors.Size()+1), {0,212,170,255} }); OnPropertyChanged(L"Colors"); }
void GridViewModel::RemoveColor() { if (m_colors.Size() > 0) { m_colors.RemoveAt(m_colors.Size()-1); OnPropertyChanged(L"Colors"); } }
void GridViewModel::ClearGrid() { m_colors.Clear(); OnPropertyChanged(L"Colors"); }
void GridViewModel::ApplyGrid() { Helpers::HardwareBridge::Instance().UpdateGlobalEffectAsync(0, 4); }

// DevicesViewModel
DevicesViewModel::DevicesViewModel() {
    m_devices = single_threaded_observable_vector<Model::DeviceItem>();
    m_zones = single_threaded_observable_vector<hstring>();
    m_found = single_threaded_observable_vector<FoundDevice>();
}
hstring DevicesViewModel::LightName() { return m_lightName; }
void DevicesViewModel::LightName(hstring const& v) { SetAndNotify(m_lightName, v, L"LightName"); }
bool DevicesViewModel::ShowGridNames() { return m_showGridNames; }
void DevicesViewModel::ShowGridNames(bool v) { SetAndNotify(m_showGridNames, v, L"ShowGridNames"); }
hstring DevicesViewModel::DeviceInfo() { return m_deviceInfo; }
void DevicesViewModel::DeviceInfo(hstring const& v) { SetAndNotify(m_deviceInfo, v, L"DeviceInfo"); }
IObservableVector<Model::DeviceItem> DevicesViewModel::Devices() { return m_devices; }
IObservableVector<hstring> DevicesViewModel::Zones() { return m_zones; }
IObservableVector<DevicesViewModel::FoundDevice> DevicesViewModel::FoundDevices() { return m_found; }
void DevicesViewModel::Detect() { /* SDK call to detect devices */ }
void DevicesViewModel::LoadMap() { /* Load mapping file */ }
void DevicesViewModel::SaveMap() { /* Save mapping file */ }
void DevicesViewModel::WhiteBalance() { /* Open white balance dialog */ }
void DevicesViewModel::ClearLight() { Helpers::HardwareBridge::Instance().SetLightAsync(0, 0, {0,0,0,255}); }
void DevicesViewModel::AddZone() { m_zones.Append(L"Zone " + to_hstring(m_zones.Size()+1)); OnPropertyChanged(L"Zones"); }
void DevicesViewModel::DeleteZone() { if (m_zones.Size() > 0) { m_zones.RemoveAt(m_zones.Size()-1); OnPropertyChanged(L"Zones"); } }
void DevicesViewModel::SelectFromList() { /* Open zone selection dialog */ }

// FansViewModel
FansViewModel::FansViewModel() {
    m_sensors = single_threaded_observable_vector<SensorData>();
    m_fans = single_threaded_observable_vector<FanData>();
    m_curve = single_threaded_observable_vector<CurvePoint>();
}
int32_t FansViewModel::PowerMode() { return m_powerMode; }
void FansViewModel::PowerMode(int32_t v) { SetAndNotify(m_powerMode, v, L"PowerMode"); }
int32_t FansViewModel::ACBoost() { return m_acBoost; }
void FansViewModel::ACBoost(int32_t v) { SetAndNotify(m_acBoost, v, L"ACBoost"); }
int32_t FansViewModel::DCBoost() { return m_dcBoost; }
void FansViewModel::DCBoost(int32_t v) { SetAndNotify(m_dcBoost, v, L"DCBoost"); }
int32_t FansViewModel::TCC() { return m_tcc; }
void FansViewModel::TCC(int32_t v) { SetAndNotify(m_tcc, v, L"TCC"); }
int32_t FansViewModel::XMP() { return m_xmp; }
void FansViewModel::XMP(int32_t v) { SetAndNotify(m_xmp, v, L"XMP"); }
IObservableVector<FansViewModel::SensorData> FansViewModel::Sensors() { return m_sensors; }
IObservableVector<FansViewModel::FanData> FansViewModel::Fans() { return m_fans; }
IObservableVector<FansViewModel::CurvePoint> FansViewModel::CurvePoints() { return m_curve; }
void FansViewModel::ApplyCurve() { /* Apply fan curve via SDK */ }
void FansViewModel::ResetCurve() { m_curve.Clear(); OnPropertyChanged(L"CurvePoints"); }
void FansViewModel::EnableOverboost() { /* Enable overboost via SDK */ }
void FansViewModel::ResetBoost() { m_tcc = 50; m_xmp = 50; OnPropertyChanged(L"TCC"); OnPropertyChanged(L"XMP"); }

// ProfilesViewModel
ProfilesViewModel::ProfilesViewModel() {
    m_profiles = single_threaded_observable_vector<ProfileEntry>();
    m_deviceEffects = single_threaded_observable_vector<DeviceEffect>();
}
hstring ProfilesViewModel::ProfileName() { return m_profileName; }
void ProfilesViewModel::ProfileName(hstring const& v) { SetAndNotify(m_profileName, v, L"ProfileName"); }
int32_t ProfilesViewModel::TriggerType() { return m_triggerType; }
void ProfilesViewModel::TriggerType(int32_t v) { SetAndNotify(m_triggerType, v, L"TriggerType"); }
hstring ProfilesViewModel::TriggerApp() { return m_triggerApp; }
void ProfilesViewModel::TriggerApp(hstring const& v) { SetAndNotify(m_triggerApp, v, L"TriggerApp"); }
hstring ProfilesViewModel::TriggerKeys() { return m_triggerKeys; }
void ProfilesViewModel::TriggerKeys(hstring const& v) { SetAndNotify(m_triggerKeys, v, L"TriggerKeys"); }
hstring ProfilesViewModel::ScriptName() { return m_scriptName; }
void ProfilesViewModel::ScriptName(hstring const& v) { SetAndNotify(m_scriptName, v, L"ScriptName"); }
bool ProfilesViewModel::DefaultProfile() { return m_defaultProfile; }
void ProfilesViewModel::DefaultProfile(bool v) { SetAndNotify(m_defaultProfile, v, L"DefaultProfile"); }
bool ProfilesViewModel::PriorityProfile() { return m_priorityProfile; }
void ProfilesViewModel::PriorityProfile(bool v) { SetAndNotify(m_priorityProfile, v, L"PriorityProfile"); }
bool ProfilesViewModel::ProfileDim() { return m_profileDim; }
void ProfilesViewModel::ProfileDim(bool v) { SetAndNotify(m_profileDim, v, L"ProfileDim"); }
bool ProfilesViewModel::ForegroundProfile() { return m_foregroundProfile; }
void ProfilesViewModel::ForegroundProfile(bool v) { SetAndNotify(m_foregroundProfile, v, L"ForegroundProfile"); }
bool ProfilesViewModel::RunScript() { return m_runScript; }
void ProfilesViewModel::RunScript(bool v) { SetAndNotify(m_runScript, v, L"RunScript"); }
bool ProfilesViewModel::FanProfile() { return m_fanProfile; }
void ProfilesViewModel::FanProfile(bool v) { SetAndNotify(m_fanProfile, v, L"FanProfile"); }
IObservableVector<ProfileEntry> ProfilesViewModel::Profiles() { return m_profiles; }
IObservableVector<DeviceEffect> ProfilesViewModel::DeviceEffects() { return m_deviceEffects; }
void ProfilesViewModel::AddProfile() { m_profiles.Append(ProfileEntry{ m_profileName, m_triggerKeys, m_defaultProfile }); OnPropertyChanged(L"Profiles"); }
void ProfilesViewModel::RemoveProfile() { if (m_profiles.Size() > 0) { m_profiles.RemoveAt(m_profiles.Size()-1); OnPropertyChanged(L"Profiles"); } }
void ProfilesViewModel::CopyActive() { /* Copy active profile */ }
void ProfilesViewModel::Reset() { m_profiles.Clear(); OnPropertyChanged(L"Profiles"); }
void ProfilesViewModel::ConfigureEffects() { /* Open device effects dialog */ }

// SettingsViewModel
SettingsViewModel::SettingsViewModel() {}
#define SETTINGS_PROP(type, name, setter) type SettingsViewModel::name() { return m_##name; } void SettingsViewModel::name(type v) { SetAndNotify(m_##name, v, L#name); }
SETTINGS_PROP(bool, StartWithWindows, StartWithWindows)
SETTINGS_PROP(bool, StartMinimized, StartMinimized)
SETTINGS_PROP(int32_t, DimmingPower, DimmingPower)
SETTINGS_PROP(bool, PowerDim, PowerDim)
SETTINGS_PROP(bool, OffPowerButton, OffPowerButton)
SETTINGS_PROP(bool, ScreenOff, ScreenOff)
SETTINGS_PROP(bool, BatDim, BatDim)
SETTINGS_PROP(bool, OffOnBattery, OffOnBattery)
SETTINGS_PROP(bool, EnableEffects, EnableEffects)
SETTINGS_PROP(bool, LightsOn, LightsOn)
SETTINGS_PROP(bool, GammaCorrection, GammaCorrection)
SETTINGS_PROP(bool, EffectsOnBattery, EffectsOnBattery)
SETTINGS_PROP(int32_t, PollingRate, PollingRate)
SETTINGS_PROP(bool, FanControl, FanControl)
SETTINGS_PROP(bool, DisableAWCC, DisableAWCC)
SETTINGS_PROP(bool, ESIFTemp, ESIFTemp)
SETTINGS_PROP(bool, KeepSystem, KeepSystem)
SETTINGS_PROP(bool, BatFan, BatFan)
SETTINGS_PROP(bool, DiskSensors, DiskSensors)
SETTINGS_PROP(bool, OverclockEnable, OverclockEnable)
SETTINGS_PROP(bool, NumlockActive, NumlockActive)
SETTINGS_PROP(bool, ActionLights, ActionLights)
SETTINGS_PROP(bool, PowerButton, PowerButton)
SETTINGS_PROP(bool, Indicator, Indicator)
SETTINGS_PROP(bool, NoDesktop, NoDesktop)
SETTINGS_PROP(bool, ResetOnWake, ResetOnWake)
SETTINGS_PROP(bool, UpdateCheck, UpdateCheck)
void SettingsViewModel::ConfigureHotkeys() { /* Open hotkey dialog */ }
void SettingsViewModel::CheckForUpdates() { /* Check GitHub for updates */ }
void SettingsViewModel::SaveSettings() { /* Save to registry via ConfigBridge */ }
void SettingsViewModel::LoadSettings() { /* Load from registry via ConfigBridge */ }
}
