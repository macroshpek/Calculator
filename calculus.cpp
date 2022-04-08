#include <Windows.h>
#include <cstring>
#include "calc_source.h"
char expression[100] = {};
bool isRunning = false;
int counter = -1;


LRESULT CALLBACK Wndproc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    //char* expression = "";
    static HWND expr_text;
    switch (uMsg) {
    case WM_DESTROY://kill all open windows
    {
        PostQuitMessage(0);
        isRunning = false;
    }break;
    case WM_QUIT://kill current window
    {
        PostQuitMessage(0);
        isRunning = false;
    }break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam)) {
        case 0:
        {
            if (counter == 0 && expression[counter] == '0') {
                break;
            }
            expression[++counter] = '0';
        }break;
        case 1:
        {
            expression[++counter] = '1';
        }break;
        case 2:
        {
            expression[++counter] = '2';
        }break;
        case 3:
        {
            expression[++counter] = '3';
        }break;
        case 4:
        {
            expression[++counter] = '4';
        }break;
        case 5:
        {
            expression[++counter] = '5';
        }break;
        case 6:
        {
            expression[++counter] = '6';
        }break;
        case 7:
        {
            expression[++counter] = '7';
        }break;
        case 8:
        {
            expression[++counter] = '8';
        }break;
        case 9:
        {
            expression[++counter] = '9';
        }break;
        case 10:
        {
            if (counter == -1 || expression[counter] == '.') {
                break;
            }
            expression[++counter] = '.';
        }break;
        case 11:
        {
            ::MessageBox(hwnd, std::to_string(Calculate(expression)).c_str(), "result", MB_OK);
            memset(expression, '\0', 50 * sizeof(char));
            //expression[49] = '\0';
            counter = -1;
        }break;
        case 12:
        {
            expression[++counter] = '/';
        }break;
        case 13:
        {
            expression[++counter] = '*';
        }break;
        case 14:
        {
            expression[++counter] = '-';
        }break;
        case 15:
        {
            memset(expression, '\0', 50 * sizeof(char));
            //expression[49] = '\0';
            counter = -1;
        }break;
        case 16:
        {
            expression[++counter] = '(';
        }break;
        case 17:
        {
            expression[++counter] = ')';
        }break;
        case 18:
        {
            expression[++counter] = '+';
        }break;
        }
        SetWindowText(expr_text, expression);
    }break;
    case WM_CREATE:
    {
        HWND button_0 = CreateWindowA("BUTTON", "0", WS_VISIBLE | WS_CHILD | WS_BORDER | BS_PUSHBUTTON, 
                                            0, 500, 200, 100, hwnd, (HMENU) 0, NULL, NULL, NULL);
        HWND button_dot = CreateWindowA("BUTTON", ",", WS_VISIBLE | WS_CHILD | WS_BORDER,
            200, 500, 100, 100, hwnd, (HMENU) 10, NULL, NULL, NULL);
        HWND button_equals = CreateWindowA("BUTTON", "=", WS_VISIBLE | WS_CHILD | WS_BORDER,
            300, 500, 100, 100, hwnd, (HMENU) 11, NULL, NULL, NULL);
        HWND button_1 = CreateWindowA("BUTTON", "1", WS_VISIBLE | WS_CHILD | WS_BORDER,
            0, 400, 100, 100, hwnd, (HMENU) 1, NULL, NULL, NULL);
        HWND button_2 = CreateWindow("BUTTON", "2", WS_VISIBLE | WS_CHILD | WS_BORDER,
            100, 400, 100, 100, hwnd, (HMENU) 2, NULL, NULL, NULL);
        HWND button_3 = CreateWindow("BUTTON", "3", WS_VISIBLE | WS_CHILD | WS_BORDER,
            200, 400, 100, 100, hwnd, (HMENU) 3, NULL, NULL, NULL);
        HWND button_divide = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | WS_BORDER,
            300, 400, 100, 100, hwnd, (HMENU) 12, NULL, NULL, NULL);
        HWND button_4 = CreateWindow("BUTTON", "4", WS_VISIBLE | WS_CHILD | WS_BORDER,
            0, 300, 100, 100, hwnd, (HMENU) 4, NULL, NULL, NULL);
        HWND button_5 = CreateWindow("BUTTON", "5", WS_VISIBLE | WS_CHILD | WS_BORDER,
            100, 300, 100, 100, hwnd, (HMENU) 5, NULL, NULL, NULL);
        HWND button_6 = CreateWindow("BUTTON", "6", WS_VISIBLE | WS_CHILD | WS_BORDER,
            200, 300, 100, 100, hwnd, (HMENU) 6, NULL, NULL, NULL);
        HWND button_multiply = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | WS_BORDER,
            300, 300, 100, 100, hwnd, (HMENU) 13, NULL, NULL, NULL);
        HWND button_7 = CreateWindow("BUTTON", "7", WS_VISIBLE | WS_CHILD | WS_BORDER,
            0, 200, 100, 100, hwnd, (HMENU) 7, NULL, NULL, NULL);
        HWND button_8 = CreateWindow("BUTTON", "8", WS_VISIBLE | WS_CHILD | WS_BORDER,
            100, 200, 100, 100, hwnd, (HMENU) 8, NULL, NULL, NULL);
        HWND button_9 = CreateWindow("BUTTON", "9", WS_VISIBLE | WS_CHILD | WS_BORDER,
            200, 200, 100, 100, hwnd, (HMENU) 9, NULL, NULL, NULL);
        HWND button_substract = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | WS_BORDER,
            300, 200, 100, 100, hwnd, (HMENU) 14, NULL, NULL, NULL);
        HWND button_zeroing = CreateWindow("BUTTON", "C", WS_VISIBLE | WS_CHILD | WS_BORDER,
            0, 100, 100, 100, hwnd, (HMENU) 15, NULL, NULL, NULL);
        HWND button_l_r_bracket = CreateWindow("BUTTON", "(", WS_VISIBLE | WS_CHILD | WS_BORDER,
            100, 100, 100, 100, hwnd, (HMENU) 16, NULL, NULL, NULL);
        HWND button_r_r_bracket = CreateWindow("BUTTON", ")", WS_VISIBLE | WS_CHILD | WS_BORDER,
            200, 100, 100, 100, hwnd, (HMENU) 17, NULL, NULL, NULL);
        HWND button_plus = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | WS_BORDER,
            300, 100, 100, 100, hwnd, (HMENU) 18, NULL, NULL, NULL);
        

        expr_text = CreateWindow("STATIC", expression, WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 50, 400, 50, hwnd, NULL, NULL, NULL);
        /*char* userText_s[20] = {};
        HWND userSavedText = GetWindowText(hwnd, &userText_s, 20);*/
        isRunning = true;
    }break;
    }
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd)
{
    const auto pClassName = "WinFrameWork";
    MSG msg;
    WNDCLASSEXA wc = {};
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Wndproc;
    wc.cbClsExtra = 0; //
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = pClassName;
    wc.hIconSm = nullptr;

    RegisterClassExA(&wc);

    HWND windowHandle = CreateWindowExA(WS_EX_OVERLAPPEDWINDOW, pClassName, "ULTRA CALCULATOR", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 420, 650, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(windowHandle, SW_SHOW);

    while (isRunning) {
        if (GetMessage(&msg, windowHandle, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}