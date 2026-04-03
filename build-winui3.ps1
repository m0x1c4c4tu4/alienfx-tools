#Requires -RunAsAdministrator
<#
.SYNOPSIS
    Builds AlienFX Control WinUI 3 for Windows 11
.DESCRIPTION
    Restores NuGet packages, builds the WinUI 3 project, and produces
    the final executable in the output directory.
.NOTES
    Requires: Visual Studio 2022 (Build Tools) + Windows 11 SDK
#>

param(
    [ValidateSet("Debug","Release")]
    [string]$Configuration = "Release",

    [ValidateSet("x64","x86","ARM64")]
    [string]$Platform = "x64",

    [switch]$Clean,

    [switch]$Package
)

$ErrorActionPreference = "Stop"
$SolutionDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectName = "alienfx-gui-winui3"
$VcProject = Join-Path $SolutionDir "$ProjectName\$ProjectName.vcxproj"
$OutputDir = Join-Path $SolutionDir "bin\$Platform\$Configuration"

Write-Host "========================================" -ForegroundColor Cyan
Write-Host " AlienFX Control WinUI 3 Build Script" -ForegroundColor Cyan
Write-Host " Configuration: $Configuration | Platform: $Platform" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan

# --- Prerequisites Check ---
Write-Host "`n[1/5] Checking prerequisites..." -ForegroundColor Yellow

$msbuild = $null
$vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (Test-Path $vsWhere) {
    $installPath = & $vsWhere -latest -requires Microsoft.Component.MSBuild -property installationPath 2>$null
    if ($installPath) {
        $msbuild = Join-Path $installPath "MSBuild\Current\Bin\MSBuild.exe"
    }
}

if (-not $msbuild -or -not (Test-Path $msbuild)) {
    Write-Host "ERROR: MSBuild not found." -ForegroundColor Red
    Write-Host "Install Visual Studio 2022 with 'Desktop development with C++' workload." -ForegroundColor Red
    Write-Host "  https://visualstudio.microsoft.com/downloads/" -ForegroundColor Gray
    exit 1
}
Write-Host "  MSBuild: $msbuild" -ForegroundColor Green

# Check Windows SDK
$sdkPath = "${env:ProgramFiles(x86)}\Windows Kits\10"
if (-not (Test-Path $sdkPath)) {
    Write-Host "WARNING: Windows 10 SDK not found at $sdkPath" -ForegroundColor Yellow
    Write-Host "  Install via VS Installer -> Individual Components -> Windows 10 SDK" -ForegroundColor Gray
} else {
    Write-Host "  Windows SDK: $sdkPath" -ForegroundColor Green
}

# Check Windows App SDK
$wasPath = "${env:ProgramFiles(x86)}\Windows App SDK"
if (-not (Test-Path $wasPath)) {
    Write-Host "WARNING: Windows App SDK not found. Will be restored via NuGet." -ForegroundColor Yellow
} else {
    Write-Host "  Windows App SDK: $wasPath" -ForegroundColor Green
}

# --- NuGet Restore ---
Write-Host "`n[2/5] Restoring NuGet packages..." -ForegroundColor Yellow

$nugetExe = Join-Path $SolutionDir ".nuget\nuget.exe"
if (-not (Test-Path $nugetExe)) {
    $nugetUrl = "https://dist.nuget.org/win-x86-commandline/latest/nuget.exe"
    $nugetDir = Join-Path $SolutionDir ".nuget"
    if (-not (Test-Path $nugetDir)) { New-Item -ItemType Directory -Path $nugetDir -Force | Out-Null }
    Write-Host "  Downloading nuget.exe..." -ForegroundColor Gray
    Invoke-WebRequest -Uri $nugetUrl -OutFile $nugetExe -UseBasicParsing
}

$packagesConfig = Join-Path $SolutionDir "$ProjectName\packages.config"
if (Test-Path $packagesConfig) {
    & $nugetExe restore $VcProject -PackagesDirectory (Join-Path $SolutionDir "packages")
    if ($LASTEXITCODE -ne 0) {
        Write-Host "ERROR: NuGet restore failed." -ForegroundColor Red
        exit 1
    }
} else {
    # Use dotnet restore for PackageReference-style projects
    Write-Host "  Using PackageReference — no packages.config needed." -ForegroundColor Gray
}

# --- Clean ---
if ($Clean) {
    Write-Host "`n[3/5] Cleaning previous build..." -ForegroundColor Yellow
    if (Test-Path $OutputDir) {
        Remove-Item -Recurse -Force $OutputDir
    }
    & $msbuild $VcProject /t:Clean /p:Configuration=$Configuration /p:Platform=$Platform /v:minimal
}

# --- Build ---
Write-Host "`n[3/5] Building $ProjectName ($Configuration|$Platform)..." -ForegroundColor Yellow

$buildArgs = @(
    $VcProject
    "/t:Build"
    "/p:Configuration=$Configuration"
    "/p:Platform=$Platform"
    "/p:WindowsPackageType=None"
    "/p:WindowsAppSDKSelfContained=true"
    "/p:CppWinRTOptimized=true"
    "/p:CppWinRTUseWinUI3=true"
    "/v:minimal"
    "/nologo"
    "/m"
)

& $msbuild @buildArgs
if ($LASTEXITCODE -ne 0) {
    Write-Host "`nERROR: Build failed with exit code $LASTEXITCODE" -ForegroundColor Red
    exit 1
}

# --- Verify Output ---
Write-Host "`n[4/5] Verifying output..." -ForegroundColor Yellow

$exePath = Join-Path $OutputDir "$ProjectName.exe"
if (Test-Path $exePath) {
    $size = (Get-Item $exePath).Length
    Write-Host "  Output: $exePath" -ForegroundColor Green
    Write-Host "  Size: $([math]::Round($size / 1MB, 2)) MB" -ForegroundColor Green
} else {
    # Try alternate output path
    $altExe = Get-ChildItem -Path $SolutionDir -Recurse -Filter "$ProjectName.exe" -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($altExe) {
        Write-Host "  Output: $($altExe.FullName)" -ForegroundColor Green
        Write-Host "  Size: $([math]::Round($altExe.Length / 1MB, 2)) MB" -ForegroundColor Green
    } else {
        Write-Host "  WARNING: Executable not found at expected location." -ForegroundColor Yellow
        Write-Host "  Search results:" -ForegroundColor Yellow
        Get-ChildItem -Path $SolutionDir -Recurse -Filter "*.exe" -ErrorAction SilentlyContinue | ForEach-Object {
            Write-Host "    $($_.FullName)" -ForegroundColor Gray
        }
    }
}

# --- Package (optional) ---
if ($Package) {
    Write-Host "`n[5/5] Creating distribution package..." -ForegroundColor Yellow
    $pkgDir = Join-Path $SolutionDir "dist\$Configuration"
    if (-not (Test-Path $pkgDir)) { New-Item -ItemType Directory -Path $pkgDir -Force | Out-Null }

    # Copy executable and dependencies
    if (Test-Path $exePath) {
        Copy-Item $exePath $pkgDir -Force
    }

    # Copy required DLLs from Windows App SDK
    $wasDlls = Get-ChildItem -Path (Join-Path $SolutionDir "packages") -Recurse -Filter "*.dll" -ErrorAction SilentlyContinue |
        Where-Object { $_.Name -match "Microsoft\.WindowsAppSDK|Microsoft\.UI\.Xaml" }
    foreach ($dll in $wasDlls) {
        Copy-Item $dll.FullName $pkgDir -Force
    }

    Write-Host "  Package: $pkgDir" -ForegroundColor Green
    Get-ChildItem $pkgDir | ForEach-Object {
        Write-Host "    $($_.Name) ($([math]::Round($_.Length / 1KB, 1)) KB)" -ForegroundColor Gray
    }
}

Write-Host "`n========================================" -ForegroundColor Cyan
Write-Host " Build Complete!" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
