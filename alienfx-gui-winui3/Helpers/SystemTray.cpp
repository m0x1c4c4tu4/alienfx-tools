#include "pch.h"
#include "Helpers/SystemTray.h"
#include <shellapi.h>

#define WM_TRAYICON (WM_USER + 1)
#define ID_TRAY_EXIT 1001
#define ID_TRAY_SETTINGS 1002
#define ID_TRAY_LIGHTS_ON 1003
#define ID_TRAY_DIMMED 1004

namespace winrt::AlienFX::Helpers
{
    SystemTray& SystemTray::Instance()
    {
        static SystemTray instance;
        return instance;
    }

    void SystemTray::Initialize(HWND hwnd, HINSTANCE hInstance)
    {
        m_nid.cbSize = sizeof(NOTIFYICONDATAW);
        m_nid.hWnd = hwnd;
        m_nid.uID = 1;
        m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        m_nid.uCallbackMessage = WM_TRAYICON;
        m_nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(1));
        wcscpy_s(m_nid.szTip, L"AlienFX Control");

        m_hMenu = CreatePopupMenu();
        AppendMenuW(m_hMenu, MF_STRING, ID_TRAY_LIGHTS_ON, L"Lights On");
        AppendMenuW(m_hMenu, MF_STRING, ID_TRAY_DIMMED, L"Dimmed");
        AppendMenuW(m_hMenu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(m_hMenu, MF_STRING, ID_TRAY_SETTINGS, L"Settings");
        AppendMenuW(m_hMenu, MF_STRING, ID_TRAY_EXIT, L"Exit");
    }

    void SystemTray::Show()
    {
        Shell_NotifyIconW(NIM_ADD, &m_nid);
        m_visible = true;
    }

    void SystemTray::Hide()
    {
        Shell_NotifyIconW(NIM_DELETE, &m_nid);
        m_visible = false;
    }

    void SystemTray::UpdateIcon(HICON icon)
    {
        m_nid.hIcon = icon;
        Shell_NotifyIconW(NIM_MODIFY, &m_nid);
    }

    void SystemTray::SetTooltip(const wchar_t* tooltip)
    {
        wcscpy_s(m_nid.szTip, tooltip);
        Shell_NotifyIconW(NIM_MODIFY, &m_nid);
    }

    void SystemTray::ShowContextMenu(HWND hwnd, POINT pt)
    {
        SetForegroundWindow(hwnd);
        TrackPopupMenu(m_hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, nullptr);
        PostMessage(hwnd, WM_NULL, 0, 0);
    }

    void SystemTray::Destroy()
    {
        if (m_visible) Hide();
        if (m_hMenu) DestroyMenu(m_hMenu);
    }

    LRESULT CALLBACK SystemTray::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (msg == WM_TRAYICON) {
            if (lParam == WM_RBUTTONUP) {
                POINT pt;
                GetCursorPos(&pt);
                Instance().ShowContextMenu(hwnd, pt);
            } else if (lParam == WM_LBUTTONDBLCLK) {
                ShowWindow(hwnd, SW_RESTORE);
            }
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}
