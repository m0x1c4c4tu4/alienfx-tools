# WinUI 3 Migration Plan — alienfx-gui

## Architecture Overview

### Layer Diagram
```
┌─────────────────────────────────────────────────┐
│              WinUI 3 XAML Layer                 │
│  (Pages, UserControls, Custom Controls, Styles) │
├─────────────────────────────────────────────────┤
│           C++/WinRT ViewModel Layer             │
│  (INotifyPropertyChanged, Commands, State Mgmt) │
├─────────────────────────────────────────────────┤
│          Hardware Abstraction Layer             │
│  (ConfigHandler, FXHelper, EventHandler wrappers)│
├─────────────────────────────────────────────────┤
│          Existing C++ SDK (UNCHANGED)           │
│  AlienFX-SDK │ alienfan-SDK │ Common │ RegHelper│
└─────────────────────────────────────────────────┘
```

### New Project Structure
```
alienfx-gui-winui3/
├── alienfx-gui-winui3.vcxproj          # WinUI 3 Desktop app (unpackaged)
├── Package.appxmanifest                 # NOT used — unpackaged
├── app.manifest                         # requireAdministrator
├── App.xaml / App.xaml.h / App.xaml.cpp
├── MainWindow.xaml / .h / .cpp
├── ViewModel/
│   ├── ViewModelBase.h                  # INotifyPropertyChanged
│   ├── MainViewModel.h/.cpp             # Shell state, navigation
│   ├── LightingViewModel.h/.cpp         # Lights tab state
│   ├── ColorsViewModel.h/.cpp           # Color effects
│   ├── EventsViewModel.h/.cpp           # Event triggers
│   ├── AmbientViewModel.h/.cpp          # Ambient mode
│   ├── HapticsViewModel.h/.cpp          # Audio haptics
│   ├── GridViewModel.h/.cpp             # Grid effects
│   ├── DevicesViewModel.h/.cpp          # Device management
│   ├── FansViewModel.h/.cpp             # Fan control
│   ├── ProfilesViewModel.h/.cpp         # Profile management
│   ├── SettingsViewModel.h/.cpp         # App settings
│   ├── DeviceItem.h/.cpp                # Model: device info
│   ├── LightItem.h/.cpp                 # Model: light info
│   ├── ProfileItem.h/.cpp               # Model: profile
│   ├── FanCurveItem.h/.cpp              # Model: fan curve point
│   └── SensorItem.h/.cpp                # Model: sensor reading
├── Pages/
│   ├── LightingPage.xaml/.h/.cpp        # Main lighting page
│   ├── ColorsPage.xaml/.h/.cpp
│   ├── EventsPage.xaml/.h/.cpp
│   ├── AmbientPage.xaml/.h/.cpp
│   ├── HapticsPage.xaml/.h/.cpp
│   ├── GridPage.xaml/.h/.cpp
│   ├── DevicesPage.xaml/.h/.cpp
│   ├── FansPage.xaml/.h/.cpp
│   ├── ProfilesPage.xaml/.h/.cpp
│   └── SettingsPage.xaml/.h/.cpp
├── Controls/
│   ├── ColorButton.xaml/.h/.cpp         # Color picker button
│   ├── LedGridControl.xaml/.h/.cpp      # LED matrix visualization
│   ├── FanCurveControl.xaml/.h/.cpp     # Fan curve graph
│   ├── GaugeControl.xaml/.h/.cpp        # Real-time gauge/meter
│   ├── FreqBarsControl.xaml/.h/.cpp     # Audio frequency bars
│   └── DeviceCard.xaml/.h/.cpp          # Device info card
├── Dialogs/
│   ├── ZoneSelectDialog.xaml/.h/.cpp    # Zone selection
│   ├── KeyPressDialog.xaml/.h/.cpp      # Hotkey capture
│   ├── WhiteBalanceDialog.xaml/.h/.cpp  # White balance
│   └── AboutDialog.xaml/.h/.cpp         # About box
├── Converters/
│   ├── ColorToBrushConverter.h/.cpp
│   ├── BoolToVisibilityConverter.h/.cpp
│   └── EnumToStringConverter.h/.cpp
├── Helpers/
│   ├── HardwareBridge.h/.cpp            # SDK → ViewModel bridge
│   ├── ConfigBridge.h/.cpp              # ConfigHandler → ViewModel
│   └── DispatcherHelper.h/.cpp          # UI thread marshaling
├── Resources/
│   ├── Colors.xaml                      # Color resources
│   ├── Styles.xaml                      # Control styles
│   └── Templates.xaml                   # Control templates
└── Assets/
    ├── Logo.png
    └── Icons/                           # Fluent icon set
```

## MVVM Design

### ViewModelBase (INotifyPropertyChanged)
```cpp
// ViewModel/ViewModelBase.h
#pragma once
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <string>

namespace winrt::AlienFX::ViewModel::implementation
{
    struct ViewModelBase : implements<ViewModelBase,
        Microsoft::UI::Xaml::Data::INotifyPropertyChanged>
    {
    public:
        event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
        
        winrt::event_token PropertyChanged(
            Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
        
    protected:
        void OnPropertyChanged(std::wstring_view propertyName);
        
        template<typename T>
        bool SetAndNotify(T& field, T&& value, std::wstring_view propertyName) {
            if (field != value) {
                field = std::forward<T>(value);
                OnPropertyChanged(propertyName);
                return true;
            }
            return false;
        }
    };
}
```

### ViewModel Hierarchy
```
MainViewModel (shell, navigation, tray state)
├── LightingViewModel (active device, active zone, light state)
│   ├── ColorsViewModel (color effects list, tempo, length)
│   ├── EventsViewModel (event list, triggers, color gradients)
│   ├── AmbientViewModel (grid zones, capture settings, scale)
│   ├── HapticsViewModel (freq groups, tact, spectrum)
│   ├── GridViewModel (effects, speed, width, phases)
│   └── DevicesViewModel (device list, detection, mapping, white balance)
├── FansViewModel (fan curves, temps, boost, power modes)
├── ProfilesViewModel (profile list, triggers, device effects)
└── SettingsViewModel (all settings, hotkeys, AWCC, ESIF)
```

### Hardware Bridge Pattern
```cpp
// Helpers/HardwareBridge.h — singleton bridging SDK to ViewModels
struct HardwareBridge {
    static HardwareBridge& Instance();
    
    // SDK passthrough — wraps existing C++ calls
    winrt::Windows::Foundation::IAsyncAction SetLightAsync(
        int deviceId, int lightId, winrt::Windows::UI::Color color);
    winrt::Windows::Foundation::IAsyncAction UpdateGlobalEffectAsync(
        int deviceId, int effectType);
    
    // Real-time monitoring
    winrt::event_token SensorUpdated(
        Windows::Foundation::TypedEventHandler<IInspectable, SensorData> const&);
    void StartMonitoring();
    void StopMonitoring();
    
private:
    HardwareBridge(); // wraps ConfigHandler*, FXHelper*, EventHandler*
    ConfigHandler* m_conf;
    FXHelper* m_fxhl;
    EventHandler* m_eve;
};
```

## Navigation Structure (NavigationView)

```
NavigationView (MainWindow)
├── Home/Dashboard          → DashboardPage (system overview, quick actions)
├── ─────────────────
├── 💡 Lighting             → LightingPage (sub-navigation via Pivot)
│   ├── Colors              → ColorsPage
│   ├── Events              → EventsPage
│   ├── Ambient             → AmbientPage
│   ├── Haptics             → HapticsPage
│   ├── Grid                → GridPage
│   └── Devices             → DevicesPage
├── 🌀 Fans                 → FansPage
├── 📋 Profiles             → ProfilesPage
├── ⚙️ Settings             → SettingsPage
├── ─────────────────
├── ℹ️ About                → ContentDialog (modal)
└── [Footer]
    └── System Tray Icon    → Native NOTIFYICONDATA (unchanged)
```

## Phase Breakdown

### Phase 1: Project Scaffold + MVVM Infrastructure
- Create new WinUI 3 Desktop vcxproj (unpackaged)
- Configure NuGet: Microsoft.WindowsAppSDK, Microsoft.Windows.CppWinRT
- Create app.manifest with requireAdministrator
- Implement ViewModelBase with INotifyPropertyChanged
- Implement HardwareBridge (wraps existing ConfigHandler, FXHelper, EventHandler)
- Implement DispatcherHelper for UI thread marshaling
- Create MainWindow.xaml with empty NavigationView shell
- Create App.xaml with resource dictionaries

### Phase 2: Core UI Shell + Navigation
- NavigationView with all menu items (icons, labels, footer)
- Navigation routing logic (page factory)
- System tray integration (NOTIFYICONDATA, unchanged from Win32)
- Window management (minimize to tray, restore)
- Basic Mica/Acrylic backdrop
- About ContentDialog
- DashboardPage (system overview placeholder)

### Phase 3: Lighting Pages
- LightingPage with Pivot for sub-tabs (Colors/Events/Ambient/Haptics/Grid/Devices)
- ColorsPage: effect list (ListView), tempo/length sliders, add/remove buttons, color pickers
- EventsPage: event list, trigger source combo, color gradient config, reorder buttons
- AmbientPage: zone selector, H/V scale sliders, reset button, ambient grid preview
- Device mapping: connect LightingViewModel to HardwareBridge
- Test: light color changes reflect on hardware in real-time

### Phase 4: Haptics, Grid, Devices Pages
- HapticsPage: freq groups list, FreqBarsControl (custom), tact slider, spectrum toggle
- GridPage: effect type combo, speed/width sliders, color phase buttons, circle/random/phase checkboxes
- DevicesPage: device list (ListView), detect button, load/save mapping, white balance dialog, grid management
- ZoneSelectDialog: ContentDialog for zone selection
- WhiteBalanceDialog: ContentDialog with RGB sliders
- Custom controls: LedGridControl, FreqBarsControl

### Phase 5: Fans, Profiles, Settings Pages
- FansPage: FanCurveControl (custom), temp/fan listboxes, boost settings, reset buttons
- ProfilesPage: profile list, add/remove, trigger config (power/app/hotkey), device effects, fan profile toggle
- SettingsPage: all settings grouped in Expander controls (startup, dimming, effects, AWCC, ESIF, hotkeys, update check)
- KeyPressDialog: ContentDialog for hotkey capture
- Test: fan curve changes apply, profile switching works, settings persist

### Phase 6: Custom Controls + Polish
- FanCurveControl: Canvas-based fan curve visualization (replaces GDI drawing)
- GaugeControl: real-time temperature/fan speed meters
- ColorButton: reusable color picker with preview
- DeviceCard: expandable device info card
- Fluent Design polish: Reveal highlight, animations, transitions
- Accessibility: keyboard navigation, screen reader labels, high contrast
- Performance: virtualization for lists, batched UI updates, dispatcher priority tuning

## Migration Dependency Map

```
Phase 1 (Scaffold)
    ↓
Phase 2 (Shell + Navigation)
    ↓
Phase 3 (Lighting Pages) ← requires HardwareBridge from Phase 1
    ↓
Phase 4 (Haptics/Grid/Devices) ← requires custom controls scaffolding
    ↓
Phase 5 (Fans/Profiles/Settings) ← independent of Phase 4, can parallelize with Phase 3
    ↓
Phase 6 (Custom Controls + Polish) ← depends on all pages existing
```

## Win32 → WinUI 3 Control Mapping

| Win32 Control | WinUI 3 Equivalent | Notes |
|---------------|-------------------|-------|
| TabControl (main) | NavigationView | Primary navigation |
| TabControl (sub) | Pivot | Secondary navigation within Lighting |
| DialogBox | ContentDialog | Modal dialogs |
| Button (BS_OWNERDRAW) | Button + custom UserControl | Color buttons, grid buttons |
| Slider | Slider | Native, styled |
| CheckBox | ToggleSwitch / CheckBox | ToggleSwitch for on/off |
| ComboBox | ComboBox | Native |
| ListBox | ListView | With DataTemplate |
| ListCtrl (report) | DataGrid / ListView | Use CommunityToolkit if needed |
| Edit | TextBox | Native |
| Static | TextBlock | Native |
| SysLink | HyperlinkButton | Native |
| HotKey control | Custom UserControl | KeyPressDialog |
| Custom GDI drawing | Canvas + XAML shapes | Fan curve, freq bars, LED grid |
| Tray icon (NOTIFYICONDATA) | NOTIFYICONDATA (unchanged) | Win32 API still works |
| ToolTip | ToolTipService | Attached property |
| ProgressBar | ProgressBar / ProgressRing | Native |
| GroupBox | Expander | Modern pattern |

## NuGet Packages
```xml
<ItemGroup>
  <PackageReference Include="Microsoft.WindowsAppSDK" Version="1.5.240802000" />
  <PackageReference Include="Microsoft.Windows.CppWinRT" Version="2.0.240405.15" />
</ItemGroup>
```

## Build Configuration (vcxproj key settings)
```xml
<PropertyGroup>
  <WindowsPackageType>None</WindowsPackageType>  <!-- Unpackaged -->
  <CppWinRTOptimized>true</CppWinRTOptimized>
  <CppWinRTUseWinUI3>true</CppWinRTUseWinUI3>
  <WindowsAppSDKSelfContained>true</WindowsAppSDKSelfContained>
</PropertyGroup>
```

## Risk Mitigation

| Risk | Impact | Mitigation |
|------|--------|------------|
| C++/WinRT XAML binding limitations | Medium | Use `{Binding}` fallback, code-behind for complex cases |
| Admin elevation with WinUI 3 | Critical | Unpackaged + app.manifest (verified working) |
| Hardware SDK compatibility | Critical | SDK stays as separate C++ lib, no changes needed |
| Real-time performance (60Hz updates) | Medium | DispatcherTimer with Low priority, batched updates |
| Custom control rendering parity | Low | Canvas-based drawing, test against original GDI output |
| Build complexity | Medium | Incremental migration — old and new coexist until cutover |
| Third-party dependencies (kiss_fft, DXGCap) | Low | Keep as separate libs, link statically |

## Testing Strategy

Per phase:
1. **Phase 1**: Build succeeds, ViewModelBase property change fires, HardwareBridge connects to SDK
2. **Phase 2**: Navigation works, tray icon responds, window minimize/restore
3. **Phase 3**: Color changes apply to hardware, effect list CRUD works, ambient preview renders
4. **Phase 4**: Haptic freq bars render, grid effects apply, device detection works
5. **Phase 5**: Fan curves apply, profile switching works, settings persist to registry
6. **Phase 6**: Custom controls match original GDI output, keyboard nav works, performance <16ms/frame

## File Manifest

### CREATE (new WinUI 3 project): ~50 files
- 1 vcxproj, 1 app.manifest
- 3 App files (xaml/h/cpp)
- 3 MainWindow files
- 13 ViewModel files (base + 12 viewmodels)
- 4 Model files
- 10 Page files (xaml/h/cpp each = 30 files)
- 6 Custom Control files (xaml/h/cpp each = 18 files)
- 4 Dialog files (xaml/h/cpp each = 12 files)
- 3 Converter files
- 3 Helper files
- 3 Resource XAML files

### MODIFY: 0 files (new project, no modifications to existing)

### KEEP (referenced, not modified):
- AlienFX-SDK/AlienFX_SDK/ (all files)
- alienfan-tools/alienfan-SDK/ (all files)
- Common/ (all files)
- RegHelperLib/ (all files)
- alienfx-gui/kiss_fft/ (all files)
- alienfx-gui/Mappings/ (all files)
- alienfx-LFX/ (all files)
