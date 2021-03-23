#include "Edit.h"


Edit::Edit(LPCWSTR name, long style, int x, int y,
	int width, int height, HWND hWndParent, HMENU id, HINSTANCE hInst) {

	_type = _T("edit");
	_name = name;
	_style = style;
	_left = x;
	_top = y;
	_width = width;
	_height = height;
	_hWndParent = hWndParent;
	_id = id;
	_hInst = hInst;
}

void Edit::setText(TCHAR* buf) {
	SetWindowText(_hWnd, buf);
}

void Edit::getText(TCHAR* buf) {
	GetWindowText(_hWnd, buf, 1000);
}