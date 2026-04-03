#pragma once
#include <ShlObj.h>
#include <string>
#include <vector>

bool EvaluteToAdmin(HWND dlg = NULL);
bool DoStopAWCC(bool flag, bool kind);
void ResetDPIScale(LPWSTR cmdLine);
DWORD WINAPI CUpdateCheck(LPVOID);
bool WindowsStartSet(bool, std::string);
std::string GetAppVersion(bool isFile = true);
void CreateToolTip(HWND, HWND&);
void CreateToolTip(HWND, HWND&, int);
HWND SetToolTip(HWND, std::string);
void SetSlider(HWND, int);
void UpdateCombo(HWND ctrl, const std::string* items, int sel = 0, std::vector<int> val = {});
void UpdateCombo(HWND ctrl, const char* items[], int sel = 0, const int val[] = NULL);
void ShowNotification(NOTIFYICONDATA* niData, std::string title, std::string message);
void SetBitMask(WORD& val, WORD mask, bool state);
bool AddTrayIcon(NOTIFYICONDATA* iconData, bool needCheck);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void BlinkNumLock(int howmany);
bool WarningBox(HWND hDlg, const char* msg);

