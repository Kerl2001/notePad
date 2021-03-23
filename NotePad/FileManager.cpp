#include "FileManager.h"

FileManager::FileManager(HWND hWnd) {
	_hWnd = hWnd;
    ZeroMemory(&_ofn, sizeof(OPENFILENAME));
    _ofn.lStructSize = sizeof(OPENFILENAME);
    _ofn.hwndOwner = hWnd;
    _ofn.lpstrFile = _szFile;
    _ofn.nMaxFile = sizeof(_szFile);
    _ofn.lpstrFilter = _T("Text\0*.txt\0");
    _ofn.nFilterIndex = 1;
    _ofn.lpstrFileTitle = NULL;
    _ofn.nMaxFileTitle = 0;
    _ofn.lpstrInitialDir = NULL;
    _ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    _hf = NULL;
    _currentFileName = NULL;
}

BOOL FileManager::SaveFileWithManager() {
    if (_currentFileName == NULL) {
        return FALSE;
    }
    _hf = CreateFile(_ofn.lpstrFile, GENERIC_READ | GENERIC_WRITE,
        0, NULL,
        OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
        NULL);
    return TRUE;
}

BOOL FileManager::SaveFileAsWithManager() {
    if (_hf != NULL) {
        CloseFileWithManager();
    }
    if (GetSaveFileName(&_ofn)) {

        int sizeFileName = _tcslen(_ofn.lpstrFile);
        _ofn.lpstrFile[sizeFileName] = L'.';
        _ofn.lpstrFile[++sizeFileName] = L't';
        _ofn.lpstrFile[++sizeFileName] = L'x';
        _ofn.lpstrFile[++sizeFileName] = L't';
        
        _hf = CreateFile(_ofn.lpstrFile, GENERIC_READ | GENERIC_WRITE,
            0, NULL,
            OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
            NULL);
        _currentFileName = _ofn.lpstrFile;
        return TRUE;
    }
    return FALSE;
}

BOOL FileManager::OpenFileWithoutChoice() {
    _hf = CreateFile(_ofn.lpstrFile, GENERIC_READ | GENERIC_WRITE,
        0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
        NULL);
    _currentFileName = _ofn.lpstrFile;
    return TRUE;
}

BOOL FileManager::OpenFileWithManager() {
    if (_hf != NULL) {
        CloseFileWithManager();
    }
    if (GetOpenFileName(&_ofn)) {
        //OFSTRUCT buf;
        
        //_hf = OpenFile((LPCSTR)_ofn.lpstrFile, &buf, OF_CREATE | OF_READWRITE | OF_SHARE_EXCLUSIVE);
        _hf = CreateFile(_ofn.lpstrFile, GENERIC_READ | GENERIC_WRITE,
            0, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
            NULL);
        
        _currentFileName = _ofn.lpstrFile;
        return TRUE;
    }
    
    return FALSE;
}


BOOL FileManager::ReadFileWithManager(TCHAR* buf, int size) {
    if (_hf != NULL) {
        DWORD bytesWritten;
        if (ReadFile(_hf, buf, size*2, &bytesWritten, NULL)) {
            buf[bytesWritten] = L'\0';
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FileManager::WriteFileWithManager(TCHAR* buf, int size) {
    if (_hf != NULL) {
        DWORD bytesWritten;
        if (WriteFile(_hf, buf, size*2, &bytesWritten, NULL)) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FileManager::CloseFileWithManager() {
    if (CloseHandle(_hf)) {
        _hf = NULL;
        return TRUE;
    }
    return FALSE;
}
