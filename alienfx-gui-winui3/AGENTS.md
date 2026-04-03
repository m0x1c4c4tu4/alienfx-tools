# ALIENFX-GUI-WINUI3 KNOWLEDGE BASE

**Generated:** 2026-04-03
**Commit:** 9db9e68
**Branch:** master

## OVERVIEW
WinUI3 rewrite of alienfx-gui using C++/WinRT + MVVM pattern. 72 files, replaces the Win32 GUI with modern XAML-based UI.

## STRUCTURE
```
alienfx-gui-winui3/
├── App.xaml.{cpp,h,idl}        # Application entry point, WinRT activation
├── MainWindow.xaml.{cpp,h,idl} # Main window with navigation frame
├── pch.h                       # Precompiled header (required first include)
├── packages.config             # NuGet packages (WinUI3, CommunityToolkit)
├── Pages/                      # 11 feature pages (44 files)
│   ├── DashboardPage           # System overview, quick actions
│   ├── LightingPage            # Per-device light control
│   ├── ColorsPage              # Color picker, palette management
│   ├── GridPage                # Grid/zone-based lighting
│   ├── AmbientPage             # Screen/audio-reactive effects
│   ├── HapticsPage             # Sound haptic feedback
│   ├── FansPage                # Fan control interface
│   ├── ProfilesPage            # Profile save/load/switch
│   ├── EventsPage              # Event triggers (app launch, power)
│   ├── DevicesPage             # Device detection, configuration
│   └── SettingsPage            # App settings, AWCC integration
├── Controls/                   # Custom XAML controls (24 files)
├── ViewModel/                  # MVVM view models (10 files)
│   ├── MainViewModel           # Root VM, navigation, state
│   ├── LightingViewModel       # Lighting state, effects
│   ├── ColorsViewModel         # Color management
│   ├── ViewModelBase           # INotifyPropertyChanged impl
│   ├── Models.h                # Data models
│   └── AllViewModels           # VM aggregation
├── Dialogs/                    # Modal dialogs (12 files)
├── Helpers/                    # Utility classes (8 files)
├── Converters/                 # XAML IValueConverter impls (4 files)
├── Resources/                  # XAML resource dictionaries
└── Assets/                     # UI images, icons
```

## WHERE TO LOOK
| Task | Location | Notes |
|------|----------|-------|
| Add new page | `Pages/` | Follow `{Name}Page.xaml.{cpp,h,idl}` pattern |
| Add VM | `ViewModel/` | Inherit `ViewModelBase`, register in `AllViewModels` |
| Custom control | `Controls/` | XAML user controls or templated controls |
| Data binding converter | `Converters/` | Implement `IValueConverter` |
| Modal dialog | `Dialogs/` | ContentDialog wrappers |
| Navigation logic | `MainWindow.xaml.cpp` | Frame navigation, page caching |
| App lifecycle | `App.xaml.cpp` | Initialization, error handling |

## CONVENTIONS
- **File pattern**: `{Name}.xaml` + `{Name}.xaml.cpp` + `{Name}.xaml.h` + `{Name}.idl`
- **IDL files**: WinRT component definitions for each page (C++/WinRT projection)
- **Precompiled header**: `#include "pch.h"` MUST be first include in every .cpp
- **MVVM**: All business logic in ViewModel, pages are thin views
- **ViewModelBase**: Implements `INotifyPropertyChanged` — all VMs inherit from this
- **NuGet**: Dependencies via `packages.config` (WinUI3, CommunityToolkit.Mvvm)
- **XAML resources**: Shared styles in `Resources/` directory

## ANTI-PATTERNS
- **Do NOT put business logic in page code-behind** — move to ViewModel
- **Do NOT skip `pch.h`** as first include — breaks precompiled headers
- **Do NOT modify IDL files manually** without understanding WinRT projection
- **Do NOT mix Win32 GUI patterns** — this is pure XAML/MVVM, different from `alienfx-gui/`

## UNIQUE STYLES
- C++/WinRT (not C#) — WinUI3 with native C++
- WinRT IDL (`.idl`) files for each page — enables XAML binding to C++/WinRT types
- AllViewModels aggregation pattern — single root VM owns all child VMs
- CommunityToolkit.Mvvm for MVVM helpers (not custom implementation)

## NOTES
- Coexists with Win32 `alienfx-gui/` — both are active, WinUI3 is the future direction
- Requires Windows App SDK (WinUI3 runtime) installed on target machine
- Build config: `Debug|x64`, `Release|x64` (no x86 for this project)
