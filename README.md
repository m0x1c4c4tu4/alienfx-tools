# AlienFx tools

> Lightweight Alienware hardware control — lights, fans, power profiles, monitoring. Replaces AWCC.

## Install

**One-liner (PowerShell):**
```powershell
irm https://raw.githubusercontent.com/m0x1c4c4tu4/alienfx-tools/master/install.ps1 | iex
```

**Or with curl:**
```cmd
curl -sS https://raw.githubusercontent.com/m0x1c4c4tu4/alienfx-tools/master/install.cmd | cmd
```

**Or download the latest MSI/ZIP from [Releases](https://github.com/m0x1c4c4tu4/alienfx-tools/releases).**

### Requirements

- Windows 10 v1903+ (64-bit) or Windows 11
- Alienware light device / Alienware ACPI BIOS (for fan control)
- Administrator rights for fan control and BIOS sensors

### First-time setup

1. **Install** using the one-liner above or download from Releases
2. **Open a new terminal** (PATH changes need a fresh session)
3. **Probe your devices** — this detects and names your lights:
   ```cmd
   alienfx probe
   ```
4. **Launch the GUI** to configure everything visually:
   ```cmd
   alienfx gui
   ```

### Quick start

```cmd
alienfx gui              # Launch AlienFX Control (full GUI)
alienfx monitor          # Launch system monitor (tray app)
alienfx fan              # Launch AlienFan Control (fan GUI)
alienfx probe            # Detect and name your devices
alienfx status           # Show connected devices and lights
alienfx setall=255,0,0   # Set all lights to red
alienfx setzone=left,0,255,0,pulse  # Pulse left zone green
alienfx setdim=128       # Set brightness to 50%
alienfx update           # Check for updates
alienfx version          # Show installed version
```

### Update

alienfx-tools checks for updates automatically in the background. When a new version is ready, you'll see a notification in the system tray. Just restart the app to apply.

Manual update check:
```cmd
alienfx update
```

Or download the latest from [Releases](https://github.com/m0x1c4c4tu4/alienfx-tools/releases).

---

## Tools included

| Tool | Description |
|------|-------------|
| [AlienFX Control](Doc/alienfx-gui.md) | AWCC alternative in ~500KB. Control lights, fans, temperatures, power settings, ambient effects, sound haptics |
| [AlienFX Monitor](Doc/alienfx-mon.md) | System monitoring — check health, pin parameters to system tray |
| [AlienFX-CLI](Doc/alienfx-cli.md) | Command-line light control and device status |
| [LightFX](Doc/LightFX.md) | Dell LightFX library emulator for games |
| [AlienFan GUI](Doc/alienfan-gui.md) | Fan control — set curves based on any temperature sensor, switch power modes |
| [AlienFan-CLI](Doc/alienfan-cli.md) | Command-line fan and power control |
| `alienfx-config.cmd` | Backup/restore/delete tool configuration from registry |

## How does it work?

### Light control

Works directly with USB/ACPI hardware devices — no drivers needed.

- **Fast** — up to 20cps on older systems, up to 120cps on modern
- **Flexible** — uncommon calls for broader effects and modes
- **Profiles** — group lights, create profiles for games/power sources/keyboard shortcuts

### Fan / power control

Unlike `SpeedFan`, `HWINFO`, or `Dell Fan Control`, this tool does **not** use direct EC (Embedded Controller) access. It uses proprietary Alienware ACPI BIOS function calls — the same ones AWCC uses.

- **Safer** — BIOS still monitors fans, no risk of fans stopping under load
- **Universal** — most Alienware/Dell G-series share the same interface
- **Sometimes the only way** — e.g., Alienware m15/m17R1 has no EC control

## Security and privacy

> **Antivirus false positives:** versions `4.2.1`–`6.4.3.2` may trigger AV detection. [Why?](https://github.com/T-Troll/alienfx-tools/wiki/Why-antivirus-complain-about-some-alienfx-tools-components%3F) Add the install folder to your AV exception list.

| Tool | Admin required? |
|------|:-:|
| `alienfan-gui` / `alienfan-cli` | Always (hardware communication) |
| `alienfx-gui` | For: Disable AWCC, BIOS sensors, Fan control |
| `alienfx-mon` | For: BIOS or Alienware monitoring |
| `alienfx-cli` | Never |

- No internet connection required (update checks are optional)
- No personal data collected. Hardware data is local-only.

## Supported hardware

**Light control:** Virtually any Alienware/Dell G-series (with Alienware keyboard) notebook and desktop, plus some Alienware mice, keyboards, and monitors.

**Fan control:** Modern Alienware/Dell G-Series notebooks (m-series, x-series, Area51m), Aurora R7+ desktops.

See the full [tested devices list](https://github.com/T-Troll/alienfx-tools/wiki/Supported-and-tested-devices-list) on the Wiki.

Device not supported? [Help add support](https://github.com/T-Troll/alienfx-tools/wiki/How-to-collect-data-for-the-new-light-device).

## Troubleshooting

### Light system freeze
Shutdown or hibernate, disconnect **all** cables (including power), wait 15 seconds, then restart.

### AlienFX-GUI/CLI freezes at startup (>6s)
If you have an Alienware monitor, disconnect the monitor USB cable or reset monitor settings to default (known hardware bug).

### Ambient effect not working
Install DirectX from [here](https://www.microsoft.com/en-us/download/details.aspx?id=35). Ambient mode requires DirectX for screen capture.

### More sensors for fan control
Install and run [Libre Hardware Monitor](https://librehardwaremonitor.org/) before launching the fan control app — it provides additional temperature sensors.

## Build from source

```
Prerequisites:
  - Visual Studio 2019+ (VS 2026 for v9.4.0+)
  - (Optional) Microsoft WDK — for V1 fan SDK builds

Steps:
  1. git clone https://github.com/m0x1c4c4tu4/alienfx-tools.git
  2. Open alienfx-tools.sln in Visual Studio
  3. Build Solution (Ctrl+Shift+B)
```

## License

MIT. Free for personal and commercial use. Modifications allowed with attribution — link back to this repo and credit the original authors.

## Credits

Functionality idea and code, new devices support, haptic and ambient algorithms by [T-Troll](https://github.com/T-Troll).  
Low-level SDK based on Gurjot95's [AlienFX_SDK](https://github.com/Gurjot95/AlienFX-SDK).  
High-level API code and alienfx-cli based on Kalbert312's [alienfx-cli](https://github.com/kalbert312/alienfx-cli).  
Spectrum Analyzer based on Tnbuig's [Spectrum-Analyzer-15.6.11](https://github.com/tnbuig/Spectrum-Analyzer-15.6.11).  
FFT subroutine utilizes [Kiss FFT](https://sourceforge.net/projects/kissfft/).  
DXGI Screen capture based on Bryal's [DXGCap](https://github.com/bryal/DXGCap).

Special thanks to [DavidLapous](https://github.com/DavidLapous) for inspiration and advice!  
Special thanks to [theotherJohnC](https://github.com/theotherJohnC) for the Performance Boost idea!  
Per-Key RGB devices testing and a lot of support by [rirozizo](https://github.com/rirozizo).  
Aurora R7 testing by [Raoul Duke](https://github.com/raould).  
Support for mouse and a lot of testing by [Billybobertjoe](https://github.com/Billybobertjoe).  
A lot of G-mode ideas and testing from [Hellohi3654](https://github.com/Hellohi3654).  
Alienware m15R6 device mapping and testing by [Professor-Plays](https://github.com/profpjlalvarenga).  
Special thanks to [PhSMu](https://github.com/PhSMu) for ideas, Dell G-series testing, and artwork.

## Support

Join the [Discord server](https://discord.gg/XU6UJbN9J5) for questions and help.

The author does not accept donations, but you can share Alienware/Dell hardware for testing — contact on Discord.
