#pragma once
#include "framework.h"
#include <Commdlg.h>

class FileManager {
private:
	OPENFILENAME _ofn;
	HWND _hWnd;
	HANDLE _hf;
	TCHAR _szFile[254];
	TCHAR* _currentFileName;
public:
	FileManager(HWND);
	
	inline void clearFileName() { _currentFileName = NULL; }
	BOOL OpenFileWithManager();
	BOOL ReadFileWithManager(TCHAR* buf, int size);
	BOOL WriteFileWithManager(TCHAR* buf, int size);
	BOOL CloseFileWithManager();
	BOOL SaveFileAsWithManager();
	BOOL SaveFileWithManager();
	BOOL OpenFileWithoutChoice(LPWSTR filename = NULL);
	//BOOL OpenExistingFileWithoutChoice();


	inline TCHAR* getCurrentFileName() {
		return _currentFileName;
	}
};