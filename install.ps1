<#
.SYNOPSIS
    One-liner installer for alienfx-tools.

.DESCRIPTION
    Downloads the latest release from GitHub and installs alienfx-tools.
    Supports MSI (preferred) and ZIP fallback.
    Creates an 'alienfx' wrapper command for update/status operations.

.USAGE
    # One-liner install
    irm https://raw.githubusercontent.com/m0x1c4c4tu4/alienfx-tools/master/install.ps1 | iex

    # Or with curl
    curl.exe -sS https://raw.githubusercontent.com/m0x1c4c4tu4/alienfx-tools/master/install.ps1 | powershell -

    # Install to custom directory
    irm ... | iex -Args @{ InstallDir = "D:\AlienFX" }

    # Skip update check
    irm ... | iex -Args @{ SkipUpdateCheck = $true }
#>

param(
    [string]$InstallDir,
    [switch]$SkipUpdateCheck
)

$ErrorActionPreference = "Stop"

# ─── Config ───────────────────────────────────────────────────────────
$Repo         = "m0x1c4c4tu4/alienfx-tools"
$ApiBase      = "https://api.github.com/repos/$Repo"
$AppDataDir   = Join-Path $env:LOCALAPPDATA "alienfx-tools"
$WrapperName  = "alienfx.cmd"
$CurrentVersion = "9.4.1"

if (-not $InstallDir) {
    $InstallDir = $AppDataDir
}

# ─── Helpers ──────────────────────────────────────────────────────────
function Write-Banner {
    Write-Host ""
    Write-Host "  ╔══════════════════════════════════════════╗" -ForegroundColor Cyan
    Write-Host "  ║       alienfx-tools — Installer          ║" -ForegroundColor Cyan
    Write-Host "  ╚══════════════════════════════════════════╝" -ForegroundColor Cyan
    Write-Host ""
}

function Write-Step   { Write-Host " ► $args" -ForegroundColor Cyan }
function Write-OK     { Write-Host "   ✓ $args" -ForegroundColor Green }
function Write-Err    { Write-Host "   ✗ $args" -ForegroundColor Red }
function Write-Warn   { Write-Host "   ! $args" -ForegroundColor Yellow }

function Get-LatestRelease {
    try {
        $json = Invoke-RestMethod -Uri "$ApiBase/releases/latest" -Headers @{
            "Accept" = "application/vnd.github.v3+json"
            "User-Agent" = "alienfx-tools-installer"
        } -ErrorAction Stop
        return $json
    } catch {
        Write-Err "Failed to fetch latest release from GitHub."
        Write-Err $_.Exception.Message
        return $null
    }
}

function Download-File {
    param([string]$Url, [string]$OutFile)

    Write-Step "Downloading: $(Split-Path $OutFile -Leaf)"

    try {
        # Try curl.exe first (faster, shows progress)
        if (Get-Command curl.exe -ErrorAction SilentlyContinue) {
            $result = & curl.exe -L -o $OutFile -w "%{http_code}" -sS $Url
            $httpCode = $result[-3..-1] -join ""
            if ($httpCode -notmatch "^2[0-9]{2}$") {
                throw "HTTP $httpCode"
            }
        } else {
            # Fallback to PowerShell downloader
            [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
            Invoke-WebRequest -Uri $Url -OutFile $OutFile -UseBasicParsing
        }

        if (-not (Test-Path $OutFile)) {
            throw "File not created after download"
        }

        $size = "{0:N1} MB" -f ((Get-Item $OutFile).Length / 1MB)
        Write-OK "Downloaded ($size)"
        return $true
    } catch {
        Write-Err "Download failed: $_"
        return $false
    }
}

function Install-ViaMSI {
    param([string]$MsiPath)

    Write-Step "Installing via MSI..."

    $logFile = Join-Path $env:TEMP "alienfx-tools-install.log"
    $process = Start-Process -FilePath "msiexec.exe" `
        -ArgumentList "/i `"$MsiPath`" /quiet /norestart /log `"$logFile`"" `
        -Wait -PassThru -NoNewWindow

    if ($process.ExitCode -eq 0 -or $process.ExitCode -eq 3010) {
        Write-OK "MSI installed successfully."
        return $true
    } else {
        Write-Warn "MSI install returned code $($process.ExitCode). Trying ZIP fallback..."
        return $false
    }
}

function Install-ViaZip {
    param([string]$ZipPath, [string]$TargetDir)

    Write-Step "Extracting to: $TargetDir"

    if (-not (Test-Path $TargetDir)) {
        New-Item -ItemType Directory -Path $TargetDir -Force | Out-Null
    }

    try {
        Expand-Archive -Path $ZipPath -DestinationPath $TargetDir -Force
        Write-OK "Extracted successfully."
        return $true
    } catch {
        Write-Err "Extraction failed: $_"
        return $false
    }
}

function Create-Wrapper {
    param([string]$TargetDir)

    Write-Step "Creating 'alienfx' wrapper command..."

    $wrapperPath = Join-Path $TargetDir $WrapperName
    $wrapperContent = @'
@echo off
setlocal enabledelayedexpansion

set "AFX_DIR=%~dp0"
set "AFX_EXE=%AFX_DIR%alienfx-cli.exe"
set "AFX_GUI=%AFX_DIR%alienfx-gui.exe"
set "AFX_MON=%AFX_DIR%alienfx-mon.exe"
set "AFX_FAN_GUI=%AFX_DIR%alienfan-gui.exe"
set "AFX_FAN_CLI=%AFX_DIR%alienfan-cli.exe"

if /i "%~1"=="update" goto :update
if /i "%~1"=="status" goto :status
if /i "%~1"=="version" goto :version
if /i "%~1"=="gui" goto :gui
if /i "%~1"=="monitor" goto :monitor
if /i "%~1"=="fan" goto :fan
if /i "%~1"=="fan-cli" goto :fancli
if /i "%~1"=="help" goto :help
if /i "%~1"=="/?" goto :help
if /i "%~1"=="-h" goto :help
if /i "%~1"=="" goto :help

REM Pass through to alienfx-cli for all other commands
"%AFX_EXE%" %*
goto :eof

:update
echo.
echo Checking for updates...
powershell -NoProfile -Command "$ErrorActionPreference='Stop'; $repo='m0x1c4c4tu4/alienfx-tools'; $latest=Invoke-RestMethod -Uri 'https://api.github.com/repos/$repo/releases/latest' -Headers @{'Accept'='application/vnd.github.v3+json';'User-Agent'='alienfx-tools'}; $current='9.4.1'; $tag=$latest.tag_name; Write-Host ''; if ($tag -ne $current) { Write-Host ' New version available: $tag (current: $current)' -ForegroundColor Yellow; Write-Host ' Download: $($latest.html_url)' -ForegroundColor Cyan; Write-Host '' } else { Write-Host ' You are up to date! (v$current)' -ForegroundColor Green; Write-Host '' }"
goto :eof

:status
echo.
echo alienfx-tools status:
echo.
if exist "%AFX_EXE%" (
    "%AFX_EXE%" status
) else (
    echo   alienfx-cli.exe not found
)
echo.
echo Installed at: %AFX_DIR%
goto :eof

:version
echo alienfx-tools v9.4.1
goto :eof

:gui
if exist "%AFX_GUI%" (
    start "" "%AFX_GUI%"
) else (
    echo alienfx-gui.exe not found at: %AFX_GUI%
)
goto :eof

:monitor
if exist "%AFX_MON%" (
    start "" "%AFX_MON%"
) else (
    echo alienfx-mon.exe not found at: %AFX_MON%
)
goto :eof

:fan
if exist "%AFX_FAN_GUI%" (
    start "" "%AFX_FAN_GUI%"
) else (
    echo alienfan-gui.exe not found at: %AFX_FAN_GUI%
)
goto :eof

:fancli
if exist "%AFX_FAN_CLI%" (
    "%AFX_FAN_CLI%" %~2 %~3 %~4 %~5
) else (
    echo alienfan-cli.exe not found at: %AFX_FAN_CLI%
)
goto :eof

:help
echo.
echo  alienfx-tools — Alienware hardware control
echo.
echo  Usage: alienfx [command] [options]
echo.
echo  Commands:
echo    update        Check for updates
echo    status        Show device status
echo    version       Show installed version
echo    gui           Launch AlienFX Control GUI
echo    monitor       Launch AlienFX Monitor (tray)
echo    fan           Launch AlienFan Control GUI
echo    fan-cli       Run AlienFan CLI
echo.
echo  Light control (passed to alienfx-cli):
echo    probe         Detect and name devices/lights
echo    setall        Set all lights: setall=R,G,B[,action]
echo    setzone       Set zone: setzone=zone,R,G,B[,action]
echo    settempo      Set animation tempo: settempo=speed
echo    setdim        Set brightness: setdim=value
echo    status        Show device/light status
echo    loop          Loop all commands
echo.
echo  Examples:
echo    alienfx probe
echo    alienfx setall=255,0,0
echo    alienfx setzone=left,0,255,0,pulse
echo    alienfx setdim=128
echo    alienfx update
echo.
echo  Docs: https://github.com/m0x1c4c4tu4/alienfx-tools
echo.
goto :eof
'@

    Set-Content -Path $wrapperPath -Value $wrapperContent -Encoding ASCII
    Write-OK "Wrapper created: $wrapperPath"
}

function Add-ToPath {
    param([string]$TargetDir)

    $currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
    if ($currentPath -notlike "*$TargetDir*") {
        Write-Step "Adding to user PATH..."
        [Environment]::SetEnvironmentVariable(
            "Path",
            "$currentPath;$TargetDir",
            "User"
        )
        $env:Path = "$env:Path;$TargetDir"
        Write-OK "Added to PATH: $TargetDir"
    } else {
        Write-OK "Already in PATH: $TargetDir"
    }
}

function Create-StartMenuShortcuts {
    param([string]$TargetDir)

    $programsPath = [Environment]::GetFolderPath("CommonPrograms")
    $folderPath = Join-Path $programsPath "AlienFX Tools"

    if (-not (Test-Path $folderPath)) {
        New-Item -ItemType Directory -Path $folderPath -Force | Out-Null
    }

    $shortcuts = @(
        @{ Name = "AlienFX Control.lnk";    Target = Join-Path $TargetDir "alienfx-gui.exe";    Icon = 0 }
        @{ Name = "AlienFX Monitor.lnk";    Target = Join-Path $TargetDir "alienfx-mon.exe";    Icon = 0 }
        @{ Name = "AlienFan Control.lnk";   Target = Join-Path $TargetDir "alienfan-gui.exe";   Icon = 0 }
        @{ Name = "AlienFX CLI.lnk";        Target = "cmd.exe";                                 Icon = 0; Args = "/k cd /d `"$TargetDir`" && alienfx" }
    )

    $shell = New-Object -ComObject WScript.Shell

    foreach ($sc in $shortcuts) {
        $linkPath = Join-Path $folderPath $sc.Name
        if (-not (Test-Path $sc.Target) -and $sc.Target -ne "cmd.exe") {
            continue
        }
        $shortcut = $shell.CreateShortcut($linkPath)
        $shortcut.TargetPath = $sc.Target
        if ($sc.Args) { $shortcut.Arguments = $sc.Args }
        $shortcut.WorkingDirectory = $TargetDir
        $shortcut.Save()
    }

    Write-OK "Start Menu shortcuts created."
}

# ─── Main ─────────────────────────────────────────────────────────────
Write-Banner

# Check Windows
if ($PSVersionTable.PSVersion.Major -lt 5) {
    Write-Err "PowerShell 5.0+ required. Current: $($PSVersionTable.PSVersion)"
    exit 1
}

$os = Get-CimInstance Win32_OperatingSystem
if ($os.Version -lt "10.0.18362") {
    Write-Err "Windows 10 v1903+ required. Current: $($os.Version)"
    exit 1
}

Write-OK "Windows $($os.Caption) v$($os.Version)"
Write-Step "Install directory: $InstallDir"
Write-Host ""

# Fetch latest release
$release = Get-LatestRelease
if (-not $release) {
    Write-Err "Cannot reach GitHub. Check your internet connection."
    exit 1
}

$tag = $release.tag_name
Write-Step "Latest release: v$tag"
Write-Host ""

# Download
$msiUrl = $null
$zipUrl = $null
foreach ($asset in $release.assets) {
    if ($asset.name -eq "alienfx-tools.msi") { $msiUrl = $asset.browser_download_url }
    if ($asset.name -eq "alienfx-tools.zip") { $zipUrl = $asset.browser_download_url }
}

$msiPath = Join-Path $env:TEMP "alienfx-tools.msi"
$zipPath = Join-Path $env:TEMP "alienfx-tools.zip"

$installed = $false

# Try MSI first
if ($msiUrl) {
    if (Download-File -Url $msiUrl -OutFile $msiPath) {
        $installed = Install-ViaMSI -MsiPath $msiPath
    }
}

# Fallback to ZIP
if (-not $installed -and $zipUrl) {
    if (Download-File -Url $zipUrl -OutFile $zipPath) {
        $installed = Install-ViaZip -ZipPath $zipPath -TargetDir $InstallDir
    }
}

if (-not $installed) {
    Write-Err "Installation failed. No usable release asset found."
    exit 1
}

# Create wrapper
Create-Wrapper -TargetDir $InstallDir

# Add to PATH
Add-ToPath -TargetDir $InstallDir

# Create shortcuts
Create-StartMenuShortcuts -TargetDir $InstallDir

# Cleanup temp files
Remove-Item $msiPath -ErrorAction SilentlyContinue
Remove-Item $zipPath -ErrorAction SilentlyContinue

# Version check
if (-not $SkipUpdateCheck) {
    Write-Host ""
    if ($tag -ne $CurrentVersion) {
        Write-Warn "Installed version (v$CurrentVersion) differs from latest release (v$tag)."
        Write-Warn "Consider downloading the latest from: $($release.html_url)"
    } else {
        Write-OK "You have the latest version: v$tag"
    }
}

# ─── Summary ──────────────────────────────────────────────────────────
Write-Host ""
Write-Host " ═══════════════════════════════════════════════════" -ForegroundColor Green
Write-Host "  Installation Complete!" -ForegroundColor Green
Write-Host " ═══════════════════════════════════════════════════" -ForegroundColor Green
Write-Host ""
Write-Host "  Installed to: $InstallDir"
Write-Host ""
Write-Host "  Quick start:"
Write-Host "    alienfx gui           # Launch GUI"
Write-Host "    alienfx monitor       # Launch system monitor"
Write-Host "    alienfx fan           # Launch fan control"
Write-Host "    alienfx probe         # Detect your devices"
Write-Host "    alienfx setall=255,0,0  # Set all lights to red"
Write-Host "    alienfx update        # Check for updates"
Write-Host ""
Write-Host "  Open a NEW terminal for PATH changes to take effect."
Write-Host ""
