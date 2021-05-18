#include "children_opt.h"

HWND CreateButton(UINT32 x, UINT32 y, UINT32 width, UINT32 height, LPSTR text, HWND parent, HINSTANCE parentHinstance, UINT btnId) {
	HWND hwndPushButton;

	hwndPushButton = CreateWindow(
		TEXT("button"),
		TEXT(text),
		//WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,                            
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
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