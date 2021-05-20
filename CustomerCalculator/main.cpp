/*
	Author: Yeuoly
	Date: 2021/5/18
*/

#include"children_opt.h"
#include"functions.h"
#include"ids.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);

void MessageLoop();

HINSTANCE hGlobalHinstance;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmd, int nShowCmd) {
	char *p = (char *)"sin(3!) + ( 2 ^ cos(2+122 * 5 * 10.125452 / 10) + 2 ^ 5 -(3 + ( 5 * 19 + 1 ) - 1/4) )";
	double result = calc(p, 0, strlen(p) - 1);
	//保存程序实例句柄
	hGlobalHinstance = hInstance;
	//初始化一个窗口的基础信息
	WNDCLASS wndcls;
	wndcls.cbClsExtra = NULL;
	wndcls.cbWndExtra = NULL;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WinProc;
	wndcls.lpszClassName = "CustomerCalculator";
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	//注册这个窗口
	if (FAILED(RegisterClass(&wndcls))) {
		MessageBox(NULL, "窗口注册失败", "警告", MB_OK);
		return -1;
	}

	RECT rect;
	SetRect(&rect, 0, 0, 1000, 600);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindow(
		"CustomerCalculator",
		"特色计算器",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		0, 0,
		(rect.right - rect.left), (rect.bottom - rect.top),
		NULL, NULL, hInstance, NULL
	);

	if (!hwnd) {
		MessageBox(NULL, "窗口创建", "警告", MB_OK);
		return -2;
	}

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	MessageLoop();

	return 0;
}

void MessageLoop() {
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) {
	switch (uMsg) {
	case WM_COMMAND:
	{
		switch (LOWORD(wp)) {
		case CC_BTN_START_ADD:
			MessageBox(hWnd, "Hello Button 1", "Demo", MB_OK);
			return 0;
		}
	}
		break;
	case WM_CREATE:
		CreateButton(5, 5, 40, 20, CC_STR_ADD_BTN_TEXT, hWnd, hGlobalHinstance, CC_BTN_START_ADD);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}