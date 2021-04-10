#pragma once
#include "framework.h"

class RegEdit {
private:
public:
	static BOOL CreateRegistryKey(HKEY hKeyParent, PWCHAR subkey);
	static BOOL WriteDwordInRegistry(HKEY hKeyParent, PWCHAR subkey, PWCHAR valueName, DWORD data);
	static BOOL readDwordValueRegistry(HKEY hKeyParent, PWCHAR subkey, PWCHAR valueName, DWORD* readData);
	static BOOL writeStringInRegistry(HKEY hKeyParent, PWCHAR subkey, PWCHAR valueName, PWCHAR strData);
	static BOOL readUserInfoFromRegistry(HKEY hKeyParent, PWCHAR subkey, PWCHAR valueName, PWCHAR* readData);
};

