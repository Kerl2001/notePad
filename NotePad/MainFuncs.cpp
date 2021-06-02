#include "MainFuncs.h"

void openFileAndPastInEdit(FileManager& file, Edit& edit) {
	if (!file.OpenFileWithManager())	return;
	TCHAR tBuf[1024];
	if (!file.ReadFileWithManager(tBuf, _tcslen(tBuf))) {
		file.CloseFileWithManager();
		return;
	}
	edit.setText(tBuf);
	file.CloseFileWithManager();
}

void openFileAndPastInEditWithoutChoice(FileManager& file, Edit& edit, LPWSTR filename) {
	file.OpenFileWithoutChoice(filename);
	TCHAR tBuf[1024];
	if (!file.ReadFileWithManager(tBuf, _tcslen(tBuf))) {
		file.CloseFileWithManager();
		return;
	}
	edit.setText(tBuf);
	file.CloseFileWithManager();
}

void saveFileAs(FileManager& file, Edit& edit) {
	if (!file.SaveFileAsWithManager())	return;
	TCHAR tBuf[1000];
	edit.getText(tBuf);
	size_t size = _tcslen(tBuf);
	tBuf[size] = 0;
	++size;
	file.WriteFileWithManager(tBuf, size);
	file.CloseFileWithManager();
}

void saveFile(FileManager& file, Edit& edit) {
	if (!file.SaveFileWithManager()) {
		saveFileAs(file, edit);
		return;
	}
	TCHAR tBuf[1000];
	edit.getText(tBuf);
	size_t size = _tcslen(tBuf);
	tBuf[size] = 0;
	++size;
	file.WriteFileWithManager(tBuf, size);
	file.CloseFileWithManager();
}

void newFile(FileManager& file, Edit& edit) {
	//if (!file.SaveFileAsWithManager())	return;
	file.OpenFileWithoutChoice();
	file.CloseFileWithManager();
	TCHAR tBuf[1024] = L"";
	edit.setText(tBuf);
	file.clearFileName();
}


BOOL CALLBACK QuitProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case CM_EXIT_WITHOUT_SAVE:
			EndDialog(hwndDlg, wParam);
			return CM_EXIT_WITHOUT_SAVE;
		case CM_EXIT_WITH_SAVE:
			EndDialog(hwndDlg, wParam);
			return CM_EXIT_WITH_SAVE;
		case IDCANCEL:
			EndDialog(hwndDlg, wParam);
			return IDCANCEL;
		}
	}
	return FALSE;
}