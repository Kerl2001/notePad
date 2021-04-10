// NotePad.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "NotePad.h"
#include <fstream>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

PWCHAR RegKeyName = (PWCHAR)L"MyNotepad";

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NOTEPAD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NOTEPAD));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NOTEPAD));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NOTEPAD);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
   
   InitCommonControls();

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static FileManager file(hWnd), file2(hWnd);
    static Button buttonSaveAs(_T("save as"), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)CM_SAVE_AS, hInst);
    static Button buttonSave(_T("save"), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)CM_SAVE, hInst);
    static Button buttonOpen(_T("open"), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)CM_OPEN, hInst);
    static Edit mainEdit(NULL, WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)313, hInst);
    static Edit pathEdit(NULL, WS_CHILD | WS_BORDER | WS_VISIBLE | ES_READONLY, 0, 0, 0, 0, hWnd, (HMENU)312, hInst);
    static ToolBar toolBar(NULL, WS_VISIBLE | WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0, hWnd, (HMENU)317, hInst);
    static Menu menu(hWnd);
    static bool firstWMSize = true;
    switch (message)
    {
    case WM_CREATE:
    {
        pathEdit.create();
        buttonOpen.create();
        buttonSave.create();
        buttonSaveAs.create();
        mainEdit.create();
        toolBar.create();

        RECT recMainWindow;
        //GetWindowRect(hWnd, &recMainWindow);
        GetClientRect(hWnd, &recMainWindow);
        int winMainWidth = recMainWindow.right - recMainWindow.left;
        int winMainHeight = recMainWindow.bottom - recMainWindow.top;// -63;
        

        pathEdit.move(1, 1+44, winMainWidth * 0.7, 30);
        buttonOpen.move(pathEdit.getRect().right + 1, 1 + 44, winMainWidth * 0.1, 30);
        buttonSave.move(buttonOpen.getRect().right + 1, 1 + 44, winMainWidth * 0.1, 30);
        buttonSaveAs.move(buttonSave.getRect().right + 1, 1 + 44, winMainWidth * 0.1, 30);
        mainEdit.move(1, 32 + 32, winMainWidth - 22, winMainHeight - 30 - 32);
        toolBar.move(0, 0, winMainWidth, 44);

        pathEdit.setFix();
        buttonOpen.setFix();
        buttonSave.setFix();
        buttonSaveAs.setFix();
        mainEdit.setFix();
        toolBar.setFix();


        menu.create();

        RECT mainWindowRect;
        RegEdit::readDwordValueRegistry(HKEY_CURRENT_USER, RegKeyName, (PWCHAR)L"top", (DWORD*)&mainWindowRect.top);
        RegEdit::readDwordValueRegistry(HKEY_CURRENT_USER, RegKeyName, (PWCHAR)L"left", (DWORD*)&mainWindowRect.left);
        RegEdit::readDwordValueRegistry(HKEY_CURRENT_USER, RegKeyName, (PWCHAR)L"right", (DWORD*)&mainWindowRect.right);
        RegEdit::readDwordValueRegistry(HKEY_CURRENT_USER, RegKeyName, (PWCHAR)L"bottom", (DWORD*)&mainWindowRect.bottom);

        PWCHAR filename = nullptr;
        RegEdit::readUserInfoFromRegistry(HKEY_CURRENT_USER, RegKeyName, (PWCHAR)L"Lastfile", &filename);

        MoveWindow(hWnd, mainWindowRect.left, mainWindowRect.top, mainWindowRect.right - mainWindowRect.left, mainWindowRect.bottom - mainWindowRect.top, FALSE);
        openFileAndPastInEditWithoutChoice(file, mainEdit, filename);
        pathEdit.setText(file.getCurrentFileName());


    }
    break;
    case WM_GETMINMAXINFO:
    {
        ((LPMINMAXINFO)lParam)->ptMinTrackSize.x = 450;
        ((LPMINMAXINFO)lParam)->ptMinTrackSize.y = 200;
        return 0;
    }
    break;
    case WM_SIZE:
    {
        
        pathEdit.recalculateWidthWithFix();
        buttonOpen.recalculateWidthWithFix();
        buttonSave.recalculateWidthWithFix();

        buttonSaveAs.recalculateWidthWithFix();

        toolBar.recalculateWidthWithFix();
        
        int winMainWidth = LOWORD(lParam);
        int winMainHeight = HIWORD(lParam);
        buttonSaveAs.move(buttonSave.getRect().right + 1, 1 + 44, winMainWidth - buttonSave.getRect().right - 1, 30);
        mainEdit.move(1, 75, winMainWidth-1, winMainHeight - 75);
        

    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case CM_OPEN:
            {
                openFileAndPastInEdit(file, mainEdit);
                pathEdit.setText(file.getCurrentFileName());
            }
            break;
            case CM_SAVE:
            {
                saveFile(file, mainEdit);
                
            }

            break;
            case CM_SAVE_AS:
            {
                saveFileAs(file, mainEdit);
                pathEdit.setText(file.getCurrentFileName());
            }
            break;
            case CM_NEW:
            {
                newFile(file, mainEdit);
                pathEdit.setText(file.getCurrentFileName());
            }
            break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:

        RECT recMainWindow;
        GetWindowRect(hWnd, &recMainWindow);
        
        RegEdit::CreateRegistryKey(HKEY_CURRENT_USER, RegKeyName);
        RegEdit::WriteDwordInRegistry(HKEY_CURRENT_USER, RegKeyName, (PWCHAR)L"top", recMainWindow.top);
        RegEdit::WriteDwordInRegistry(HKEY_CURRENT_USER, RegKeyName, (PWCHAR)L"left", recMainWindow.left);
        RegEdit::WriteDwordInRegistry(HKEY_CURRENT_USER, RegKeyName, (PWCHAR)L"right", recMainWindow.right);
        RegEdit::WriteDwordInRegistry(HKEY_CURRENT_USER, RegKeyName, (PWCHAR)L"bottom", recMainWindow.bottom);

        TCHAR fileName[256];
        pathEdit.getText(fileName);
        RegEdit::writeStringInRegistry(HKEY_CURRENT_USER, RegKeyName, (PWCHAR)L"Lastfile", fileName);


        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
