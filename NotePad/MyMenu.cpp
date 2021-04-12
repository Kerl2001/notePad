#include "MyMenu.h"

Menu::Menu(HWND hWnd) {
	_hWnd = hWnd;
}

BOOL Menu::CreateMenuItem(HMENU hMenu, LPWSTR str, UINT ulns, UINT uCom,
	HMENU hSubMenu, BOOL flag, UINT fType) {
    
    MENUITEMINFO mii; mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STATE | MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
    mii.fType = fType;
    mii.fState = MFS_ENABLED;
    mii.dwTypeData = str; mii.cch = sizeof(str);
    mii.wID = uCom; mii.hSubMenu = hSubMenu;
    return InsertMenuItem(hMenu, ulns, flag, &mii);
}

void Menu::create() {
    
    _hMainMenu = CreateMenu();
    _hFileMenu = CreatePopupMenu();
    int i = 0;
    CreateMenuItem(_hFileMenu, (LPWSTR)L"&Oкрыть файл\t Ctrl+O", i++, CM_OPEN, NULL, FALSE, MFT_STRING);
    CreateMenuItem(_hFileMenu, (LPWSTR)L"&Сохранить файл\t Ctrl+S", i++, CM_SAVE, NULL, FALSE, MFT_STRING);
    CreateMenuItem(_hFileMenu, (LPWSTR)L"Сохранить файл как\t Ctrl+Shift+S", i++, CM_SAVE_AS, NULL, FALSE, MFT_STRING);
    CreateMenuItem(_hFileMenu, NULL, i++, 0, NULL, FALSE, MFT_SEPARATOR);
    CreateMenuItem(_hFileMenu, (LPWSTR)L"&Выход\t Alt+F4", i++, 1004, NULL, FALSE, MFT_STRING);

    _hEditMenu = CreatePopupMenu();
    i = 0;
    CreateMenuItem(_hEditMenu, (LPWSTR)L"&Копировать\t Ctrl+C", i++, 2001, NULL, FALSE, MFT_STRING);
    CreateMenuItem(_hEditMenu, (LPWSTR)L"&Вырезать\t Ctrl+X", i++, 2002, NULL, FALSE, MFT_STRING);
    CreateMenuItem(_hEditMenu, (LPWSTR)L"&Вставить\t Ctrl+V", i++, 2003, NULL, FALSE, MFT_STRING);
    CreateMenuItem(_hEditMenu, (LPWSTR)L"&Отмена\t Ctrl+Z", i++, 2004, NULL, FALSE, MFT_STRING);

    i = 0;
    CreateMenuItem(_hMainMenu, (LPWSTR)L"&Файл", i++, 0, _hFileMenu, FALSE, MFT_STRING);
    CreateMenuItem(_hMainMenu, (LPWSTR)L"&Правка", i++, 0, _hEditMenu, FALSE, MFT_STRING);
    SetMenu(_hWnd, _hMainMenu); DrawMenuBar(_hWnd);
}