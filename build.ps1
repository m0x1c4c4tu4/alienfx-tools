<#
.SYNOPSIS
    Build alienfx-tools solution and MSI installer from terminal.
    Downloads VS Build Tools if not present, then compiles everything.

.DESCRIPTION
    1. Checks for Visual Studio Build Tools / VS 2019+
    2. Downloads & installs VS Build Tools + Installer Projects extension if missing
    3. Builds all projects (Release|x64)
    4. Builds the MSI installer (Install/Release/alienfx-tools.msi)

.USAGE
    .\build.ps1
    .\build.ps1 -Configuration Release
    .\build.ps1 -SkipInstaller   # Build binaries only, skip MSI
    .\build.ps1 -ForceDownload   # Always download fresh VS Build Tools
#>

param(
    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Release",

    [switch]$SkipInstaller,
    [switch]$ForceDownload
)

$ErrorActionPreference = "Stop"

# ─── Colors ───────────────────────────────────────────────────────────
function Write-Step   { Write-Host "► $args" -ForegroundColor Cyan }
function Write-OK     { Write-Host "  ✓ $args" -ForegroundColor Green }
function Write-Err    { Write-Host "  ✗ $args" -ForegroundColor Red }
function Write-Warn   { Write-Host "  ! $args" -ForegroundColor Yellow }

# ─── Paths ────────────────────────────────────────────────────────────
$ScriptDir   = Split-Path -Parent $MyInvocation.MyCommand.Definition
$Solution    = Join-Path $ScriptDir "alienfx-tools.sln"
$InstallProj = Join-Path $ScriptDir "Install\Install.vdproj"
$OutputDir   = Join-Path $ScriptDir "x64\$Configuration"
$MsiOutput   = Join-Path $ScriptDir "Install\$Configuration\alienfx-tools.msi"

if (-not (Test-Path $Solution)) {
    Write-Err "alienfx-tools.sln not found at: $Solution"
    exit 1
}

# ─── Step 1: Find MSBuild ─────────────────────────────────────────────
function Find-MsBuild {
    Write-Step "Looking for MSBuild..."

    # Try vswhere (ships with VS 2017+)
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vswhere) {
        $installPath = & $vswhere -latest -products * -requires Microsoft.Component.MSBuild -property installationPath 2>$null
        if ($installPath) {
            $msbuild = Join-Path $installPath "MSBuild\Current\Bin\MSBuild.exe"
            if (-not (Test-Path $msbuild)) {
                $msbuild = Join-Path $installPath "MSBuild\15.0\Bin\MSBuild.exe"
            }
            if (Test-Path $msbuild) {
                Write-OK "Found MSBuild: $msbuild"
                return $msbuild
            }
        }
    }

    # Try PATH
    $msbuild = Get-Command msbuild -ErrorAction SilentlyContinue
    if ($msbuild) {
        Write-OK "Found MSBuild in PATH: $($msbuild.Source)"
        return $msbuild.Source
    }

    return $null
}

# ─── Step 2: Download & Install VS Build Tools ────────────────────────
function Install-BuildTools {
    Write-Step "Visual Studio Build Tools not found. Downloading..."

    $BootstrapUrl = "https://aka.ms/vs/17/release/vs_BuildTools.exe"
    $BootstrapPath = Join-Path $env:TEMP "vs_BuildTools.exe"

    # Check 64-bit vs 32-bit
    if (-not (Test-Path $BootstrapPath) -or $ForceDownload) {
        Write-Step "Downloading VS Build Tools bootstrapper..."
        curl.exe -L -o $BootstrapPath $BootstrapUrl -#
        if (-not (Test-Path $BootstrapPath)) {
            Write-Err "Download failed. Check internet connection."
            exit 1
        }
    }

    Write-Step "Installing VS Build Tools (this takes ~5-15 min)..."
    Write-Warn "This requires Administrator privileges."

    $workloads = @(
        "Microsoft.VisualStudio.Workload.VCTools"           # C++ desktop
        "Microsoft.VisualStudio.Component.VC.ATL"            # ATL for installer
        "Microsoft.VisualStudio.Component.VC.CMake.Project"  # CMake support
        "Microsoft.VisualStudio.Component.Windows11SDK.22621" # Win11 SDK
    ) -join " "

    $argsList = @(
        "--quiet", "--wait", "--norestart", "--nocache"
        "--add $workloads"
        "--installPath `"${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\BuildTools`""
    ) -join " "

    $process = Start-Process -FilePath $BootstrapPath -ArgumentList $argsList -Wait -PassThru -Verb RunAs

    if ($process.ExitCode -ne 0 -and $process.ExitCode -ne 3010) {
        Write-Err "VS Build Tools installation failed (exit code: $($process.ExitCode))"
        exit 1
    }

    Write-OK "VS Build Tools installed successfully."

    # Install Installer Projects extension for .vdproj support
    Install-InstallerExtension
}

function Install-InstallerExtension {
    Write-Step "Installing Microsoft Visual Studio Installer Projects extension..."

    $ExtensionUrl = "https://marketplace.visualstudio.com/_apis/public/gallery/publishers/VisualStudioClient/vsextensions/MicrosoftVisualStudio2022InstallerProjects/latest/vspackage"
    $ExtensionPath = Join-Path $env:TEMP "InstallerProjects.vsix"

    curl.exe -L -o $ExtensionPath $ExtensionUrl -#

    if (-not (Test-Path $ExtensionPath)) {
        Write-Warn "Failed to download Installer Projects extension. MSI build may fail."
        Write-Warn "You can still build binaries. Download manually from:"
        Write-Warn "https://marketplace.visualstudio.com/items?itemName=VisualStudioClient.MicrosoftVisualStudio2022InstallerProjects"
        return
    }

    $vsixInstaller = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\resources\app\ServiceHub\Services\Microsoft.VisualStudio.Setup.Service\VSIXInstaller.exe"
    if (-not (Test-Path $vsixInstaller)) {
        $vsixInstaller = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\VSIXInstaller.exe"
    }

    if (Test-Path $vsixInstaller) {
        Write-Step "Installing extension (may require interaction)..."
        Start-Process -FilePath $vsixInstaller -ArgumentList "/quiet /a $ExtensionPath" -Wait -PassThru
        Write-OK "Installer Projects extension installed."
    } else {
        Write-Warn "VSIXInstaller not found. Install extension manually after build tools."
    }
}

# ─── Step 3: Build ────────────────────────────────────────────────────
function Build-Solution {
    param([string]$MsBuild)

    Write-Step "Building solution: $Configuration|x64"

    $buildArgs = @(
        "`"$Solution`""
        "/p:Configuration=$Configuration"
        "/p:Platform=x64"
        "/m"                          # Parallel build
        "/v:minimal"                  # Minimal output
        "/nologo"
    ) -join " "

    Write-Step "Running: MSBuild $buildArgs"

    $process = Start-Process -FilePath $MsBuild -ArgumentList $buildArgs -Wait -PassThru -NoNewWindow

    if ($process.ExitCode -ne 0) {
        Write-Err "Build failed (exit code: $($process.ExitCode))"
        exit 1
    }

    Write-OK "Solution built successfully."
    Write-OK "Output: $OutputDir\"
}

function Build-Installer {
    param([string]$MsBuild)

    Write-Step "Building MSI installer..."

    if (-not (Test-Path $InstallProj)) {
        Write-Err "Installer project not found: $InstallProj"
        exit 1
    }

    $buildArgs = @(
        "`"$InstallProj`""
        "/p:Configuration=$Configuration"
        "/p:Platform=x64"
        "/v:minimal"
        "/nologo"
    ) -join " "

    Write-Step "Running: MSBuild $buildArgs"

    $process = Start-Process -FilePath $MsBuild -ArgumentList $buildArgs -Wait -PassThru -NoNewWindow

    if ($process.ExitCode -ne 0) {
        Write-Err "MSI build failed (exit code: $($process.ExitCode))"
        Write-Warn "You may need to install the Installer Projects extension:"
        Write-Warn "https://marketplace.visualstudio.com/items?itemName=VisualStudioClient.MicrosoftVisualStudio2022InstallerProjects"
        exit 1
    }

    if (Test-Path $MsiOutput) {
        $size = "{0:N1} MB" -f ((Get-Item $MsiOutput).Length / 1MB)
        Write-OK "MSI created: $MsiOutput ($size)"
    } else {
        Write-Warn "Build succeeded but MSI not found at expected path."
        Write-Step "Searching for output..."
        Get-ChildItem -Path (Join-Path $ScriptDir "Install") -Recurse -Filter "*.msi" -ErrorAction SilentlyContinue | ForEach-Object {
            Write-OK "  Found: $($_.FullName)"
        }
    }
}

# ─── Main ─────────────────────────────────────────────────────────────
Write-Host ""
Write-Host "═══════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "  alienfx-tools — Terminal Build Script" -ForegroundColor Magenta
Write-Host "═══════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""

# Find or install MSBuild
$msbuild = Find-MsBuild
if (-not $msbuild) {
    Write-Warn "MSBuild not found on this system."
    Write-Step "This script will download and install Visual Studio Build Tools."
    Write-Warn "Requires: ~3-5 GB disk, Administrator rights, 5-15 min install time."
    Write-Host ""

    $confirm = Read-Host "Continue with installation? (y/N)"
    if ($confirm -ne "y" -and $confirm -ne "Y") {
        Write-Step "Aborted. Install VS Build Tools manually, then run this script again."
        exit 0
    }

    Install-BuildTools
    $msbuild = Find-MsBuild

    if (-not $msbuild) {
        Write-Err "MSBuild still not found after installation. Try reopening this terminal."
        exit 1
    }
}

# Build solution
Build-Solution -MsBuild $msbuild

# Build installer (unless skipped)
if (-not $SkipInstaller) {
    Build-Installer -MsBuild $msbuild
}

Write-Host ""
Write-Host "═══════════════════════════════════════════════════" -ForegroundColor Green
Write-Host "  Build Complete!" -ForegroundColor Green
Write-Host "═══════════════════════════════════════════════════" -ForegroundColor Green
Write-Host ""
Write-Host "Binaries: $OutputDir\"
if (Test-Path $MsiOutput) {
    Write-Host "Installer: $MsiOutput"
}
Write-Host ""
