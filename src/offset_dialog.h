#pragma once
#include <windows.h>

namespace offset_dialog {
bool Show(HWND parent, int curX, int curY, int& outX, int& outY);
}
