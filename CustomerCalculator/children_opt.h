#pragma once
#include<Windows.h>

HWND CreateButton(UINT32 x, UINT32 y, UINT32 width, UINT32 height, LPSTR text, HWND parent, HINSTANCE parentHinstance, UINT btnId);

HWND CreateEditor(UINT32 x, UINT32 y, UINT32 width, UINT32 height, HWND parent, HINSTANCE parentHinstance, UINT editorId, ULONG32 style);