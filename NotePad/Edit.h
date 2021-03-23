#pragma once
#include "framework.h"
#include "MyWindow.h"

class Edit : public MyWin {
private:
	TCHAR _buf[1024];
public:
	Edit(LPCWSTR, long, int, int, int, int, HWND, HMENU, HINSTANCE);
	void setText(TCHAR* buf);
	void getText(TCHAR* buf);
};