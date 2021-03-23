#pragma once
#include "MyWindow.h"
#include <CommCtrl.h>

class ToolBar : public MyWin {
private:
	HIMAGELIST _hImageList = NULL;
public:
	ToolBar(LPCWSTR, long, int, int, int, int, HWND, HMENU, HINSTANCE);
	virtual void create();
	void setButtons();
};