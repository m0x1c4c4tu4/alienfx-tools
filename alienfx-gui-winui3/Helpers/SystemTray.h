#pragma once
#include <windows.h>
#include <shellapi.h>

namespace winrt::AlienFX::Helpers
{
    struct SystemTray
    {
        static SystemTray& Instance();

        void Initialize(HWND hwnd, HINSTANCE hInstance);
        void Show();
        void Hide();
        void UpdateIcon(HICON icon);
        void SetTooltip(const wchar_t* tooltip);
        void AddMenuItem(const wchar_t* text, UINT id);
        void ShowContextMenu(HWND hwnd, POINT pt);
        void Destroy();

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:
        SystemTray() = default;
        NOTIFYICONDATAW m_nid{};
        HMENU m_hMenu{ nullptr };
        bool m_visible{ false };
    };
}
