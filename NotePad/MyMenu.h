#pragma once
#include "framework.h"

class Menu {
private:
	HMENU _hMainMenu, _hFileMenu, _hEditMenu;
	HWND _hWnd;
	
public:

	Menu(HWND hWnd);
	BOOL CreateMenuItem(HMENU hMenu, LPWSTR str, UINT ulns, UINT uCom,
		HMENU hSubMenu, BOOL flag, UINT fType);
	void create();
 };