#include "MyWindow.h"

void MyWin::create() {
	_hWnd = CreateWindow(_type, _name, _style, _left, _top, _width, _height, _hWndParent, (HMENU)_id, _hInst, NULL);
}

void MyWin::move(int left, int top, int width, int height) {
	MoveWindow(_hWnd, left, top, width, height, (BOOL)1);
	_left = left;
	_top = top;
	_width = width;
	_height = height;
}

RECT MyWin::getRect() {
	RECT rec = { _left, _top, _left + _width, _top + _height };
	return rec;
}

void MyWin::setFix() {
	_isFix = true;
	RECT recParentWindow;
	GetWindowRect(_hWndParent, &recParentWindow);
	_ratioLeft = float(_left) / (recParentWindow.right - recParentWindow.left);
	_ratioTop = float(_top) / (recParentWindow.bottom - recParentWindow.top);
	_ratioWidth = float(_width) / (recParentWindow.right - recParentWindow.left);
	_ratioHeight = float(_height) / (recParentWindow.bottom - recParentWindow.top);
}

void MyWin::recalculateSizeWithFix() {
	if (!_isFix) return;

	RECT recParentWindow;
	GetWindowRect(_hWndParent, &recParentWindow);
	
	_left = _ratioLeft * (recParentWindow.right - recParentWindow.left);
	_top = _ratioTop * (recParentWindow.bottom - recParentWindow.top);
	_width = _ratioWidth * (recParentWindow.right - recParentWindow.left);
	_height = _ratioHeight * (recParentWindow.bottom - recParentWindow.top);

	MoveWindow(_hWnd, _left, _top, _width, _height, (BOOL)1);
}

void MyWin::recalculateWidthWithFix() {
	if (!_isFix) return;

	RECT recParentWindow;
	GetWindowRect(_hWndParent, &recParentWindow);

	_left = _ratioLeft * (recParentWindow.right - recParentWindow.left);
	_width = _ratioWidth * (recParentWindow.right - recParentWindow.left);

	MoveWindow(_hWnd, _left, _top, _width, _height, (BOOL)1);
}
