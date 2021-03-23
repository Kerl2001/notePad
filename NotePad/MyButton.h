#pragma once
#include "framework.h"
#include "MyWindow.h"

class Button : public MyWin {
public:
	Button(LPCWSTR, long, int, int, int, int, HWND, HMENU, HINSTANCE);
};