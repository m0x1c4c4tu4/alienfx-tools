@echo off
setlocal

:: alienfx-tools — One-liner installer
:: Usage:
::   curl -sS https://raw.githubusercontent.com/m0x1c4c4tu4/alienfx-tools/master/install.cmd | cmd
::   or download from https://github.com/m0x1c4c4tu4/alienfx-tools/releases

powershell -NoProfile -ExecutionPolicy Bypass -Command "irm https://raw.githubusercontent.com/m0x1c4c4tu4/alienfx-tools/master/install.ps1 | iex"
