#pragma once
#include "framework.h"
#include "FileManager.h"
#include "Edit.h"

void openFileAndPastInEdit(FileManager& file, Edit& edit);
void saveFileAs(FileManager& file, Edit& edit);
void saveFile(FileManager& file, Edit& edit);
void newFile(FileManager& file, Edit& edit);