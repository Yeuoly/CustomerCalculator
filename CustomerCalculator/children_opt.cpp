#include "children_opt.h"

HWND CreateButton(UINT32 x, UINT32 y, UINT32 width, UINT32 height, LPSTR text, HWND parent, HINSTANCE parentHinstance, UINT btnId) {
	HWND hwndPushButton = CreateWindow(
		TEXT("button"),
		TEXT(text),
		//WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,                            
		WS_CHILD | WS_VISIBLE | WS_SYSMENU,
		x, y,
		width, height,
		parent,
		(HMENU)btnId,
		parentHinstance,
		NULL
	);
	if (!hwndPushButton) {
		MessageBox(NULL, "创建按钮失败", "警告", MB_OK);
		return NULL;
	}
	return hwndPushButton;
}

HWND CreateEditor(UINT32 x, UINT32 y, UINT32 width, UINT32 height, HWND parent, HINSTANCE parentHinstance, UINT editorId, ULONG32 style) {
	style = style | WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE;
	HWND hwnd = CreateWindow(
		TEXT("edit"),
		TEXT(""),
		style,
		x, y, width, height,
		parent,
		(HMENU)editorId,
		parentHinstance,
		NULL
	);
	if (!hwnd) {
		MessageBox(NULL, "创建编辑框失败", "警告", MB_OK);
		return NULL;
	}
	return hwnd;
}