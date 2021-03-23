#pragma once
#include "framework.h"
//#include "NotePad.h"

class MyWin {
protected:
	HMENU _id;
	HWND _hWnd, _hWndParent;
	int _width, _height, _top, _left;
	HINSTANCE _hInst;
	LPCWSTR _name;

	bool _isFix;
	float _ratioLeft, _ratioTop, _ratioWidth, _ratioHeight;

	long _style;

	LPCWSTR _type;

	MyWin(){}

public:

	virtual void create();
	void move(int left, int top, int width, int height);
	RECT getRect();
	inline HWND getHWND() { return _hWnd; }

	void setFix();
	inline void offFix() { _isFix = false; }

	void recalculateSizeWithFix();
	void recalculateWidthWithFix();

};