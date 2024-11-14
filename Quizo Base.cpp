//░       ░░░  ░░░░  ░░        ░░        ░░░      ░░░        ░░░      ░░░       ░░░  ░░░░  ░\\
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
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <thread>
#include <vector>
#include <wininet.h>
#include <urlmon.h>
#include <cstdlib>
#include <string>
#include <cstdio> 



using namespace Gdiplus;
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")

std::vector<std::vector<std::wstring>> questionVariations = {
    {L"Pregunta 1: Cual es la capital de Francia?", L"Pregunta 1: Que ciudad es la capital de Francia?", L"Pregunta 1: En que ciudad esta la capital de Francia?"},
    {L"Pregunta 2: Cual es el numero mas pequeno?", L"Pregunta 2: Que numero es menor?", L"Pregunta 2: Cual es el menor de estos numeros?"},
    {L"Pregunta 3: Cual es el color del cielo en un dia claro?", L"Pregunta 3: Que color tiene el cielo en un dia despejado?", L"Pregunta 3: De que color es el cielo en un dia soleado?"}
};

std::vector<std::vector<std::wstring>> answers = {
    {L"Londres", L"París", L"Roma", L"Madrid"},
    {L"3", L"1", L"5", L"2"},
    {L"Rojo", L"Azul", L"Verde", L"Amarillo"}
};

std::wstring urlEncode(const std::wstring& str) {
    std::wstring encoded;
    wchar_t hex[4];
    for (wchar_t c : str) {
        if ((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z') || (c >= L'0' && c <= L'9') || c == L'-' || c == L'_' || c == L'.' || c == L'~') {
            encoded += c;
        }
        else {
            swprintf(hex, sizeof(hex) / sizeof(hex[0]), L"%%%02X", c);
            encoded += hex;
        }
    }
    return encoded;
}

int currentQuestion = 0;
std::vector<std::wstring> allAnswers;
std::wstring deviceName;

std::wstring getWindowTitle(HWND hwnd) {
    wchar_t windowTitle[256];
    GetWindowText(hwnd, windowTitle, 256);
    return std::wstring(windowTitle);
}

// Función para obtener el nombre de la computadora
std::string getComputerName() {
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
    if (GetComputerNameA(computerName, &size)) {
        return std::string(computerName);
    }
    else {
        return "Unknown Computer";
    }
}
void updateQuestion(HWND hwnd) {
    if (currentQuestion >= questionVariations.size()) {
        std::wstring finalMessage = L"Has completado todas las preguntas.";
        MessageBox(hwnd, finalMessage.c_str(), L"¡Gracias!", MB_OK | MB_ICONINFORMATION);
        DestroyWindow(hwnd);
        return;
    }

    SetWindowText(GetDlgItem(hwnd, 1), questionVariations[currentQuestion][0].c_str());
    for (int i = 0; i < 4; ++i) {
        SetWindowText(GetDlgItem(hwnd, 2 + i), answers[currentQuestion][i].c_str());
    }
}

void sendAnswersToWeb(const std::wstring& teamName, const std::vector<std::wstring>& answers) {
    std::wstring encodedTeamName = urlEncode(teamName);
    std::wstring encodedAnswers;

    for (size_t i = 0; i < answers.size(); ++i) {
        if (!encodedAnswers.empty()) {
            encodedAnswers += L"&";
        }
        encodedAnswers += L"answer" + std::to_wstring(i + 1) + L"=" + urlEncode(answers[i]);
    }

    std::wstring url = L"https://byte-storm.katsito.xyz/proyects/QUIZO/submit_answer.php?team=" + encodedTeamName + L"&" + encodedAnswers + L"&device=" + urlEncode(deviceName);

    std::wcout << L"URL: " << url << std::endl; // Imprimir URL para depuración

    HRESULT hr = URLDownloadToFileW(NULL, url.c_str(), L"response_log.txt", 0, NULL);
    if (SUCCEEDED(hr)) {
        std::wcout << L"Response sent successfully." << std::endl;
    }
    else {
        std::wcout << L"Failed to send response." << std::endl;
    }
}

LRESULT CALLBACK SurveyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hQuestionLabel, hAnswerButtons[4];
    static HFONT hFont;
    static HBRUSH hBackgroundBrush;
    static std::wstring teamName = L"Ciencias :D"; // Replace with dynamic team name if needed

    switch (uMsg) {
    case WM_CREATE:
        hFont = CreateFont(
            22,                        // Font height
            0,                         // Font width (0 means default width)
            0,                         // Angle of the font
            0,                         // Base line of the font
            FW_NORMAL,                 // Font weight
            FALSE,                     // Italic
            FALSE,                     // Underline
            FALSE,                     // Strike out
            DEFAULT_CHARSET,           // Character set
            OUT_DEFAULT_PRECIS,        // Output precision
            CLIP_DEFAULT_PRECIS,       // Clipping precision
            CLEARTYPE_QUALITY,         // Font quality
            DEFAULT_PITCH,             // Pitch and family
            L"Segoe UI"                // Font name
        );

        hBackgroundBrush = CreateSolidBrush(RGB(240, 240, 240)); // Background color

        hQuestionLabel = CreateWindowEx(
            0, L"STATIC", NULL,
            WS_CHILD | WS_VISIBLE | SS_CENTER | SS_NOPREFIX,
            10, 20, 460, 60, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL
        );
        SendMessage(hQuestionLabel, WM_SETFONT, (WPARAM)hFont, TRUE);
        SetBkMode(GetDC(hwnd), TRANSPARENT); // Make background of the text transparent
        SetTextColor(GetDC(hwnd), RGB(0, 0, 0)); // Set text color

        for (int i = 0; i < 4; ++i) {
            hAnswerButtons[i] = CreateWindowEx(
                0, L"BUTTON", NULL,
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT | BS_CENTER,
                50 + (i % 2) * 200, 100 + (i / 2) * 70, 180, 50, hwnd, (HMENU)(2 + i), ((LPCREATESTRUCT)lParam)->hInstance, NULL
            );
            SendMessage(hAnswerButtons[i], WM_SETFONT, (WPARAM)hFont, TRUE);
            // Simplify button styling
        }

        updateQuestion(hwnd);
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) >= 2 && LOWORD(wParam) <= 5) {
            int answerIndex = LOWORD(wParam) - 2;
            std::wstring selectedAnswer = answers[currentQuestion][answerIndex];

            allAnswers.push_back(selectedAnswer);

            ++currentQuestion;
            updateQuestion(hwnd);
        }
        return 0;

    case WM_KEYDOWN:
        if (wParam == 'C') {
            DestroyWindow(hwnd);
        }
        return 0;

    case WM_DESTROY:
        if (currentQuestion >= questionVariations.size()) {
            sendAnswersToWeb(teamName, allAnswers);
        }
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WaitOperatorWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        CreateWindowEx(
            0, L"STATIC", L"Esperar al operador o administrador, ya se contactaran contigo rapidamente!.",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            10, 50, 460, 50, hwnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL
        );
        return 0;

    case WM_KEYDOWN:
        if (wParam == 'C') {
            DestroyWindow(hwnd);
            system("explorer.exe");
            printf("SISTEMA CERRADO");
        }
        return 0;

    case WM_DESTROY: // realmente esta señal no se envia ya que no debe aparecer el boton de cerrar la ventana, hasta que se precione la letra "c"
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void createWaitOperatorWindow() {
    LPCWSTR CLASS_NAME = L"Ventana Principal";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WaitOperatorWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST,
        CLASS_NAME,
        L"Esperar al operador",
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (hwnd == NULL) {
        return;
    }

    ShowWindow(hwnd, SW_SHOWMAXIMIZED);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void createSurveyWindow() {
    const wchar_t CLASS_NAME[] = L"SurveyWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = SurveyWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST,
        CLASS_NAME,
        L"Encuesta",
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (hwnd == NULL) {
        return;
    }

    wchar_t computerName[256];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
    GetComputerName(computerName, &size);
    deviceName = computerName;

    std::wcout << L"Device Name: " << deviceName << std::endl;

    ShowWindow(hwnd, SW_SHOWMAXIMIZED);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    createWaitOperatorWindow();
}

void phone_message() {
    std::string titulo = "DETECCION:";
    std::string computerName = getComputerName();
    std::string mensaje = "Dispositivo: " + computerName;

    // Escapa las comillas dobles en el título y el mensaje
    for (size_t pos = 0; (pos = titulo.find("\"", pos)) != std::string::npos; pos += 2) {
        titulo.insert(pos, "\\");
    }
    for (size_t pos = 0; (pos = mensaje.find("\"", pos)) != std::string::npos; pos += 2) {
        mensaje.insert(pos, "\\");
    }

    // Enviar la notificación de alta prioridad
    std::string command = "adb shell cmd notification post -t \"" + titulo + "\" -S bigtext \"" + mensaje + "\" \"" + mensaje + "\"";
    std::system(command.c_str());
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    std::wstring title = getWindowTitle(hwnd);

    if (title.find(L"ChatGPT") != std::wstring::npos) {
        wchar_t computerName[256];
        DWORD size = sizeof(computerName) / sizeof(computerName[0]);
        GetComputerName(computerName, &size);

        phone_message();

        std::wstring message = L"Se detecto ChatGPT en dispositivo: ";

        message += computerName;

        MessageBox(NULL, message.c_str(), L"Detección", MB_OK | MB_ICONINFORMATION);

        DWORD processId;
        GetWindowThreadProcessId(hwnd, &processId);
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
        if (hProcess != NULL) {
            TerminateProcess(hProcess, 0);
            CloseHandle(hProcess);
        }
    }
    else if (title.find(L"Copilot") != std::wstring::npos) {
        wchar_t computerName[256];
        DWORD size = sizeof(computerName) / sizeof(computerName[0]);
        GetComputerName(computerName, &size);

        std::wstring message = L"Se detecto Copilot en dispositivo: ";
        message += computerName;

        MessageBox(NULL, message.c_str(), L"Detección", MB_OK | MB_ICONINFORMATION);

        DWORD processId;
        GetWindowThreadProcessId(hwnd, &processId);
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
        if (hProcess != NULL) {
            TerminateProcess(hProcess, 0);
            CloseHandle(hProcess);
        }
    }
    else if (title.find(L"Perplexity") != std::wstring::npos) {
        wchar_t computerName[256];
        DWORD size = sizeof(computerName) / sizeof(computerName[0]);
        GetComputerName(computerName, &size);

        std::wstring message = L"Se detecto Perplexity en dispositivo: ";
        message += computerName;

        MessageBox(NULL, message.c_str(), L"Detección", MB_OK | MB_ICONINFORMATION);

        DWORD processId;
        GetWindowThreadProcessId(hwnd, &processId);
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
        if (hProcess != NULL) {
            TerminateProcess(hProcess, 0);
            CloseHandle(hProcess);
        }
    }

    return TRUE;
}

void detectChatGPT() {
    std::wcout << L"Iniciando Menu..." << std::endl;
    while (true) {
        EnumWindows(EnumWindowsProc, 0);
        Sleep(1000);
    }
}

void terminateExplorer() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return;
    }

    do {
        if (wcscmp(pe32.szExeFile, L"explorer.exe") == 0) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
            if (hProcess != NULL) {
                TerminateProcess(hProcess, 0);
                CloseHandle(hProcess);
            }
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

void blockCtrlAltDel() {
    // Nota: Bloquear Ctrl+Alt+Del no es generalmente posible desde aplicaciones en modo usuario debido a restricciones de seguridad
    // y solo se puede hacer en versiones antiguas de Windows o en escenarios específicos.
    // Esta función queda como un marcador de posición para indicar esta limitación.
}

int main() {
    // terminateExplorer(); // Terminar explorer.exe al inicio
    blockCtrlAltDel();   // Bloquear Ctrl+Alt+Del (no funcional en versiones modernas de Windows)
    system("taskkill /f /im explorer.exe");
    std::thread messageWindowThread(createSurveyWindow);

    detectChatGPT();
    messageWindowThread.join();
    return 0;
}
