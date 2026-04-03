# ALIENFAN-TOOLS KNOWLEDGE BASE

**Generated:** 2026-04-03
**Commit:** 9db9e68
**Branch:** master

## OVERVIEW
Fan control subsystem — 7 sub-projects managing Alienware/Dell G-series fans via ACPI BIOS calls. V1 and V2 SDKs coexist.

## STRUCTURE
```
alienfan-tools/
├── alienfan-SDK/               # V1 fan SDK + hardware layer
│   ├── alienfan-low/           # Hardware-level fan interface (ACPI calls)
│   └── [SDK files]             # V1 SDK public API
├── alienfan-SDK_v2/            # V2 fan SDK (newer, preferred)
├── alienfan-gui/               # Fan GUI app (7 files)
├── alienfan-cli/               # Fan CLI app (3 files)
├── alienfan-mon/               # Fan monitoring (3 files)
├── alienfan-curve/             # Fan curve logic (.vcxitems shared)
└── alienfan-shared/            # Shared config items (.vcxitems shared)
```

## WHERE TO LOOK
| Task | Location | Notes |
|------|----------|-------|
| Hardware fan control | `alienfan-SDK/alienfan-low/` | Lowest-level ACPI BIOS calls |
| V1 SDK API | `alienfan-SDK/` | Older SDK, used by Release_V1 config |
| V2 SDK API | `alienfan-SDK_v2/` | Newer SDK, preferred for new development |
| Fan curve logic | `alienfan-curve/` | Shared items (.vcxitems), used by GUI + CLI |
| Shared config | `alienfan-shared/` | Shared items (.vcxitems), common config |
| GUI app | `alienfan-gui/` | Win32 GUI for fan control |
| CLI app | `alienfan-cli/` | Command-line fan control |
| Monitoring | `alienfan-mon/` | Fan monitoring tray app |

## CONVENTIONS
- **Shared items**: `alienfan-curve/` and `alienfan-shared/` are `.vcxitems` — consumed by GUI, CLI, mon
- **V1 vs V2**: `Release_V1` build config links against V1 SDK (requires WDK); default uses V2
- **Admin required**: All fan tools need Administrator rights (ACPI BIOS access blocked from user mode)
- **Entry points**: `alienfan-cli.cpp` (CLI), `alienfan-gui/` (GUI), `alienfan-mon/` (monitoring)

## ANTI-PATTERNS
- **Do NOT mix V1 and V2 SDK calls** — they have different APIs, pick one per build config
- **Do NOT modify `.vcxitems` SharedItemsImports manually** — solution manages via NestedProjects
- **Do NOT run fan tools without admin rights** — ACPI calls will silently fail

## UNIQUE STYLES
- ACPI BIOS function calls (not direct EC access like SpeedFan) — safer, BIOS still monitors
- Fan curve logic extracted as shared items — reused across GUI, CLI, monitoring
- GitHub update check built-in to GUI and monitoring apps

## NOTES
- V2 SDK is the direction of travel — prefer V2 for new features
- WDK required only if building `Release_V1` config
- Fan curve shared items mean changes to `alienfan-curve/` affect GUI, CLI, and mon simultaneously
