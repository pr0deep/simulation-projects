#pragma once

#include "resource.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND CreateHWND(HINSTANCE,const wchar_t*,const wchar_t*);
