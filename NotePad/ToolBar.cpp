#include "ToolBar.h"

ToolBar::ToolBar(LPCWSTR name, long style, int x, int y, int width, int height,
					HWND hWndParent, HMENU id, HINSTANCE hInst) {
	
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

void ToolBar::create() {
    /*HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
        WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
        hWndParent, NULL, hInst, NULL);*/

    _hWnd = CreateWindowEx(0, TOOLBARCLASSNAME, _name, _style, _left, _top, _width, _height, _hWndParent, _id, _hInst, NULL);
    setButtons();
}

void ToolBar::setButtons() {

    const int ImageListID = 0;
    const int numButtons = 10;
    const int bitmapSize = 16;

    const DWORD buttonStyles = BTNS_AUTOSIZE;

    // Create the image list.
    _hImageList = ImageList_Create(bitmapSize, bitmapSize,   // Dimensions of individual bitmaps.
        ILC_COLOR16 | ILC_MASK,   // Ensures transparent background.
        numButtons, 0);

    // Set the image list.
    SendMessage(_hWnd, TB_SETIMAGELIST,
        (WPARAM)ImageListID,
        (LPARAM)_hImageList);

    // Load the button images.
    SendMessage(_hWnd, TB_LOADIMAGES,
        (WPARAM)IDB_STD_SMALL_COLOR,
        (LPARAM)HINST_COMMCTRL);

    // Initialize button info.
    // IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.

    TBBUTTON tbButtons[numButtons] =
    {
        { MAKELONG(STD_FILENEW,  ImageListID), CM_NEW,  TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"New" },
        { MAKELONG(STD_FILEOPEN, ImageListID), CM_OPEN, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Open"},
        { MAKELONG(STD_FILESAVE, ImageListID), CM_SAVE, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Save"},
        { MAKELONG(STD_FILESAVE, ImageListID), CM_SAVE_AS, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Save As..." },
        { MAKELONG(STD_DELETE, ImageListID), 125, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Quit" },
        { MAKELONG(STD_COPY, ImageListID), 126, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Copy" },
        { MAKELONG(STD_CUT, ImageListID), 127, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Cut" },
        { MAKELONG(STD_PASTE, ImageListID), 128, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Paste" },
        { MAKELONG(STD_UNDO, ImageListID), 124, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Undo" },
        { MAKELONG(STD_HELP, ImageListID), 124, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Info" },
    };

    // Add buttons.
    SendMessage(_hWnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
    SendMessage(_hWnd, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

    // Resize the toolbar, and then show it.
    SendMessage(_hWnd, TB_AUTOSIZE, 0, 0);
}