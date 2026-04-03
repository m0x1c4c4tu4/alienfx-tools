# ALIENFX-TOOLS KNOWLEDGE BASE

**Generated:** 2026-04-03
**Commit:** 9db9e68
**Branch:** master

## OVERVIEW
Lightweight Alienware hardware control suite — lights, fans, power profiles, monitoring. C++/Win32 + C#/WinUI3, Visual Studio. Replaces AWCC. 182 files, ~22k LOC.

## STRUCTURE
```
alienfx-tools/
├── alienfx-tools.sln          # Master VS solution (VS 2019+)
├── alienfx-config.cmd          # Registry backup/restore script
├── Common/                     # Shared utility library (vcxproj)
├── RegHelperLib/               # Registry helper library
├── AlienFX-SDK/                # Low-level light device SDK
│   └── AlienFX_SDK/            # Core SDK implementation
├── alienfx-LFX/                # Shared items: LightFX API emulation
├── LightFX/                    # LightFX DLL emulator (standalone)
├── alienfx-gui/                # Main GUI app (Win32, 43 files)
│   ├── Mappings/               # Device light mappings
│   └── kiss_fft/               # Third-party FFT library
├── alienfx-gui-winui3/         # WinUI3 GUI rewrite (MVVM, 72 files)
│   ├── Pages/                  # 11 feature pages (Dashboard, Lighting, Fans, etc.)
│   ├── Controls/               # Custom UI controls
│   ├── ViewModel/              # MVVM view models
│   ├── Dialogs/                # Modal dialogs
│   ├── Helpers/                # Utility classes
│   └── Converters/             # XAML value converters
├── alienfx-mon/                # System monitoring tray app
├── alienfx-cli/                # Command-line light control
├── alienfan-tools/             # Fan control subsystem (7 sub-projects)
│   ├── alienfan-SDK/           # V1 fan SDK + alienfan-low
│   ├── alienfan-SDK_v2/        # V2 fan SDK
│   ├── alienfan-gui/           # Fan GUI app
│   ├── alienfan-cli/           # Fan CLI app
│   ├── alienfan-mon/           # Fan monitoring
│   ├── alienfan-curve/         # Fan curve logic (shared items)
│   └── alienfan-shared/        # Shared config items
├── DPTF/                       # Intel DPTF driver files (copy to System32)
├── Doc/                        # User documentation per-tool
└── Install/                    # MSI installer project (vdproj)
```

## WHERE TO LOOK
| Task | Location | Notes |
|------|----------|-------|
| Light control (GUI, Win32) | `alienfx-gui/` | Main app, 35 cpp/h files |
| Light control (GUI, WinUI3) | `alienfx-gui-winui3/` | New MVVM rewrite, 11 pages |
| Light control (CLI) | `alienfx-cli/` | Minimal, uses AlienFX_SDK + alienfx-LFX |
| Light SDK | `AlienFX-SDK/AlienFX_SDK/` | Core USB/ACPI device communication |
| Fan control | `alienfan-tools/` | 7 sub-projects, SDK_v2 is newer |
| Fan SDK | `alienfan-tools/alienfan-SDK/` | V1 + alienfan-low (hardware layer) |
| Monitoring | `alienfx-mon/` | Tray app, BIOS/Alienware sensors |
| LightFX emulation | `LightFX/` + `alienfx-LFX/` | DLL emulator for games |
| Shared utilities | `Common/` | Cross-project helpers |
| Registry helpers | `RegHelperLib/` | Config persistence |
| Device mappings | `alienfx-gui/Mappings/` | Per-device light definitions |

## CODE MAP
| Symbol | Type | Location | Role |
|--------|------|----------|------|
| AlienFX_SDK | Library | `AlienFX-SDK/AlienFX_SDK/` | Low-level USB HID + ACPI device API |
| alienfan-SDK | Library | `alienfan-tools/alienfan-SDK/` | Fan control via ACPI BIOS calls |
| alienfan-low | Library | `alienfan-tools/alienfan-SDK/alienfan-low/` | Hardware-level fan interface |
| Common | Library | `Common/` | Shared utilities across all projects |
| RegHelperLib | Library | `RegHelperLib/` | Registry read/write helpers |
| LightFX | DLL | `LightFX/` | Game-compatible LightFX API emulator |

## CONVENTIONS
- **Project type**: `.vcxproj` (C++), `.vcxitems` (shared items), `.sln` (solution)
- **Shared items**: `.vcxitems` files used for cross-project code sharing (alienfan-shared, alienfan-curve, alienfan-mon, alienfx-LFX)
- **Configurations**: `Debug|x64`, `Debug|x86`, `Release|x64`, `Release|x86`, `Release_V1|x64`, `Release_V1|x86`
- **Release_V1**: Build against older V1 fan SDK (requires WDK)
- **Header guards**: `#pragma once` (70+ files), `#ifndef _H` only in kiss_fft (third-party)
- **Naming**: Classes PascalCase, functions/variables camelCase, project dirs kebab-case
- **Includes**: Relative for project headers, angle brackets for system libs, `pch.h` precompiled in WinUI3
- **No linting/formatting configs**: Relies on VS defaults
- **No test framework**: No unit tests, no test configs

## ANTI-PATTERNS
- **Do NOT modify `.vcxitems` SharedItemsImports manually** — solution manages these via NestedProjects
- **Do NOT run without probing first** — `alienfx-gui` or `alienfx-cli probe` required to set light names
- **Monitor USB bug** — if alienfx-gui/cli freezes >6s at start on Alienware monitor, disconnect monitor USB or reset to defaults
- **Light system freeze recovery** — disconnect all cables (including power) for 15s, not just restart
- **AV false positives** — versions 4.2.1–6.4.3.2 may trigger antivirus; add exception, not a virus
- **Admin rights required** — for BIOS sensors, fan control, AWCC disable (ESIF blocked from user account)

## UNIQUE STYLES
- Direct USB/ACPI hardware access — no driver installation needed
- ACPI BIOS function calls for fan control (not direct EC access like SpeedFan)
- Third-party libs bundled: kiss_fft (FFT), DXGCap (screen capture), Spectrum-Analyzer
- GitHub update check built-in (alienfan-gui, alienfx-mon, alienfx-gui)
- Device mapping files in `alienfx-gui/Mappings/` for per-hardware light definitions
- Two GUI implementations coexist: Win32 (`alienfx-gui/`) and WinUI3 (`alienfx-gui-winui3/`)

## COMMANDS
```bash
# Build: Open alienfx-tools.sln in Visual Studio 2019+ → Build Solution
# Config backup/restore: alienfx-config.cmd (no args for usage)
# CLI probe: alienfx-cli probe
# CLI set boost: alienfx-cli setover
# Intel DPTF: copy DPTF/* to %WINDIR%\System32\drivers\DriverData\Intel\DPTF\dv\
```

## NOTES
- Windows 10 v1903+ 64-bit only
- x86 configs exist but build to x64 (x86 ActiveCfg → x64)
- AMD Ryzen ACPI not yet supported (TODO)
- DirectX required for Ambient effect mode (screen capture)
- Libre Hardware Monitor integration provides additional sensors
