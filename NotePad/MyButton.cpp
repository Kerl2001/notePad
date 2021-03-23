#include "MyButton.h"


Button::Button(LPCWSTR name, long style, int x, int y,
	int width, int height, HWND hWndParent, HMENU id, HINSTANCE hInst){
	
	_type = _T("button");
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
