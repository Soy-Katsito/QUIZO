//░       ░░░  ░░░░  ░░        ░░        ░░░      ░░░        ░░░      ░░░       ░░░  ░░░░  ░\\
//▒  ▒▒▒▒  ▒▒▒  ▒▒  ▒▒▒▒▒▒  ▒▒▒▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒▒   ▒▒   ▒\\
//▓       ▓▓▓▓▓    ▓▓▓▓▓▓▓  ▓▓▓▓▓      ▓▓▓▓▓      ▓▓▓▓▓▓  ▓▓▓▓▓  ▓▓▓▓  ▓▓       ▓▓▓        ▓\\
//█  ████  █████  ████████  █████  ██████████████  █████  █████  ████  ██  ███  ███  █  █  █\\
//█       ██████  ████████  █████        ███      ██████  ██████      ███  ████  ██  ████  █\\

// Copyright 2024 ByteStorm & Katsito

// Todos los derechos reservados. Ninguna parte de este código puede ser utilizada, modificada, o redistribuida sin el permiso explícito del autor.

// Mirar "LICENSE" para mayor informacion del producto y licencia de el.

#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <tlhelp32.h>

#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

HHOOK keyboardHook;

void InitGDIPlus(ULONG_PTR& gdiplusToken) {
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

void ShutdownGDIPlus(ULONG_PTR& gdiplusToken) {
    GdiplusShutdown(gdiplusToken);
}

void CloseExplorer() {
    system("taskkill /f /im explorer.exe");
}

void StartExplorer() {
    system("start explorer.exe");
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
        if (pKeyboard->vkCode == VK_LWIN || pKeyboard->vkCode == VK_RWIN ||
            (pKeyboard->vkCode == VK_TAB && GetAsyncKeyState(VK_MENU)) ||
            (pKeyboard->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL))) {
            return 1;
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        Graphics graphics(hdc);
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdc, &ps.rcPaint, hBrush);
        DeleteObject(hBrush);

        FontFamily fontFamily(L"Segoe UI");
        Font font(&fontFamily, 36, FontStyleBold, UnitPixel);
        PointF point(50.0f, 50.0f);
        SolidBrush solidBrush(Color(255, 0, 0, 0));

        graphics.DrawString(L"Funciona", -1, &font, point, &solidBrush);

        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_CLOSE:
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main() {
    ULONG_PTR gdiplusToken;
    InitGDIPlus(gdiplusToken);

    LPCWSTR CLASS_NAME = L"Ventana Principal";
    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    RegisterClass(&wc);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        CLASS_NAME,
        L"Ventana",
        WS_POPUP,
        0, 0, screenWidth, screenHeight,
        NULL, NULL, wc.hInstance, NULL
    );

    if (hwnd == NULL) {
        std::cerr << "No se pudo crear la ventana.\n";
        ShutdownGDIPlus(gdiplusToken);
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);

    ShowCursor(FALSE);

    CloseExplorer();

    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (!keyboardHook) {
        std::cerr << "No se pudo instalar el hook del teclado.\n";
        ShutdownGDIPlus(gdiplusToken);
        return 0;
    }

    MSG msg = {};
    while (true) {
        if (GetAsyncKeyState('Q') & 0x8000) {
            PostQuitMessage(0);
            break;
        }

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }

        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, screenWidth, screenHeight, SWP_NOMOVE | SWP_NOSIZE);
        SetFocus(hwnd);
    }

    ShowCursor(TRUE);

    UnhookWindowsHookEx(keyboardHook);

    StartExplorer();

    ShutdownGDIPlus(gdiplusToken);

    return 0;
}
