#Requires -Version 5.1
<#
.SYNOPSIS
    Checks if the system meets prerequisites for building AlienFX Control WinUI 3.
#>

$ErrorActionPreference = "Continue"
$allPassed = $true

function Check-Prerequisite {
    param([string]$Name, [scriptblock]$Check, [string]$InstallUrl)

    Write-Host "Checking: $Name ... " -NoNewline
    try {
        $result = & $Check
        if ($result) {
            Write-Host "OK ($result)" -ForegroundColor Green
        } else {
            Write-Host "OK" -ForegroundColor Green
        }
    } catch {
        Write-Host "FAILED" -ForegroundColor Red
        Write-Host "  Install: $InstallUrl" -ForegroundColor Gray
        $script:allPassed = $false
    }
}

Write-Host "========================================" -ForegroundColor Cyan
Write-Host " AlienFX WinUI 3 Build Prerequisites" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# OS Check
Check-Prerequisite "Windows 10 1903+ / Windows 11" {
    $os = Get-CimInstance Win32_OperatingSystem
    $build = [int]$os.BuildNumber
    if ($build -ge 18362) { "Build $build" } else { throw "Build $build < 18362" }
} "https://www.microsoft.com/software-download/windows11"

# Architecture
Check-Prerequisite "x64 Architecture" {
    if ($env:PROCESSOR_ARCHITECTURE -eq "AMD64") { "x64" } else { throw "$env:PROCESSOR_ARCHITECTURE" }
} "Requires 64-bit Windows"

# Visual Studio
Check-Prerequisite "Visual Studio 2022 (Build Tools)" {
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vsWhere) {
        $vs = & $vsWhere -latest -requires Microsoft.Component.MSBuild -property displayName 2>$null
        if ($vs) { $vs } else { throw "Not found" }
    } else { throw "vswhere.exe not found" }
} "https://visualstudio.microsoft.com/downloads/"

# C++ Workload
Check-Prerequisite "Desktop development with C++" {
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vsWhere) {
        $workload = & $vsWhere -latest -requires Microsoft.VisualStudio.Workload.NativeDesktop -property displayName 2>$null
        if ($workload) { "Installed" } else { throw "Missing workload" }
    } else { throw "vswhere.exe not found" }
} "VS Installer -> Desktop development with C++"

# Windows SDK
Check-Prerequisite "Windows 10 SDK (10.0.17763.0+)" {
    $sdkPath = "${env:ProgramFiles(x86)}\Windows Kits\10\Include"
    if (Test-Path $sdkPath) {
        $versions = Get-ChildItem $sdkPath -Directory | Sort-Object Name -Descending | Select-Object -First 1
        if ($versions) { $versions.Name } else { throw "No SDK versions found" }
    } else { throw "SDK not found" }
} "VS Installer -> Individual Components -> Windows 10 SDK"

# Windows App SDK
Check-Prerequisite "Windows App SDK" {
    $wasPath = "${env:ProgramFiles(x86)}\Windows App SDK"
    if (Test-Path $wasPath) { "Found at $wasPath" } else { "Will be restored via NuGet" }
} "NuGet restore handles this automatically"

# C++/WinRT
Check-Prerequisite "C++/WinRT" {
    $cppwinrtPath = "${env:LOCALAPPDATA}\Microsoft\CppWinRT"
    if (Test-Path $cppwinrtPath) { "Found" } else { "Will be restored via NuGet" }
} "NuGet: Microsoft.Windows.CppWinRT"

# Git
Check-Prerequisite "Git" {
    $git = Get-Command git -ErrorAction SilentlyContinue
    if ($git) { & git --version } else { throw "Not found" }
} "https://git-scm.com/download/win"

# Disk Space
Check-Prerequisite "Disk Space (>5 GB free)" {
    $drive = Split-Path $PSScriptRoot -Qualifier
    $disk = Get-CimInstance Win32_LogicalDisk -Filter "DeviceID='$drive'"
    $freeGB = [math]::Round($disk.FreeSpace / 1GB, 2)
    if ($freeGB -gt 5) { "$freeGB GB free" } else { throw "Only $freeGB GB free" }
} "Free up disk space"

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
if ($allPassed) {
    Write-Host " All prerequisites met! Ready to build." -ForegroundColor Green
    Write-Host " Run: .\build-winui3.ps1" -ForegroundColor Cyan
} else {
    Write-Host " Some prerequisites are missing. Install them and re-run." -ForegroundColor Red
    exit 1
}
Write-Host "========================================" -ForegroundColor Cyan
