/*
	Author: Yeuoly
	Date: 2021/5/18
	Finished: 2021/5/21
*/

#include"children_opt.h"
#include"functions.h"
#include"ids.h"
#include"error.h"
#include<string>

struct WindowItemInfo {
	UINT id;
	HWND hwnd;
};

typedef struct {
	WindowItemInfo hEdtMan;
	WindowItemInfo hEdtAns;
} WindowItem;

static WindowItem hItems;

HINSTANCE hGlobalHinstance;
HWND hGlobalMainHwnd;

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);

//整一个多线程，这里用来实时刷新计算结果
DWORD WINAPI TimerProc(LPVOID lp);

void MessageLoop();

void CreateBtnGroup(HWND hWnd, HFONT hFont, HFONT hFuncFont) {
	//SendMessage(CreateButton(615, 440, 100, 90, (LPSTR)"pause", hWnd, hGlobalHinstance, CC_BTN_MUSIC), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(615, 440, 200, 90, (LPSTR)"0", hWnd, hGlobalHinstance, CC_BTN_0), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(815, 440, 100, 90, (LPSTR)".", hWnd, hGlobalHinstance, CC_BTN_DOT), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(615, 350, 100, 90, (LPSTR)"1", hWnd, hGlobalHinstance, CC_BTN_1), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(715, 350, 100, 90, (LPSTR)"2", hWnd, hGlobalHinstance, CC_BTN_2), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(815, 350, 100, 90, (LPSTR)"3", hWnd, hGlobalHinstance, CC_BTN_3), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(615, 260, 100, 90, (LPSTR)"4", hWnd, hGlobalHinstance, CC_BTN_4), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(715, 260, 100, 90, (LPSTR)"5", hWnd, hGlobalHinstance, CC_BTN_5), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(815, 260, 100, 90, (LPSTR)"6", hWnd, hGlobalHinstance, CC_BTN_6), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(615, 170, 100, 90, (LPSTR)"7", hWnd, hGlobalHinstance, CC_BTN_7), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(715, 170, 100, 90, (LPSTR)"8", hWnd, hGlobalHinstance, CC_BTN_8), WM_SETFONT, (WPARAM)hFont, NULL);
	SendMessage(CreateButton(815, 170, 100, 90, (LPSTR)"9", hWnd, hGlobalHinstance, CC_BTN_9), WM_SETFONT, (WPARAM)hFont, NULL);

	SendMessage(CreateButton(5, 290, 100, 55, (LPSTR)"+", hWnd, hGlobalHinstance, CC_BTN_ADD), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(105, 290, 100, 55, (LPSTR)"-", hWnd, hGlobalHinstance, CC_BTN_SUB), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(205, 290, 100, 55, (LPSTR)"*", hWnd, hGlobalHinstance, CC_BTN_MUL), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(304, 290, 100, 55, (LPSTR)"/", hWnd, hGlobalHinstance, CC_BTN_DIV), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(405, 290, 100, 55, (LPSTR)"mod", hWnd, hGlobalHinstance, CC_BTN_INV), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(505, 290, 100, 55, (LPSTR)"C", hWnd, hGlobalHinstance, CC_BTN_CLS), WM_SETFONT, (WPARAM)hFuncFont, NULL);

	SendMessage(CreateButton(5, 350, 100, 55, (LPSTR)"sin", hWnd, hGlobalHinstance, CC_BTN_SIN), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(105, 350, 100, 55, (LPSTR)"cos", hWnd, hGlobalHinstance, CC_BTN_COS), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(205, 350, 100, 55, (LPSTR)"tan", hWnd, hGlobalHinstance, CC_BTN_TAN), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(304, 350, 100, 55, (LPSTR)"arcsin", hWnd, hGlobalHinstance, CC_BTN_ASI), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(405, 350, 100, 55, (LPSTR)"arccos", hWnd, hGlobalHinstance, CC_BTN_ACS), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(505, 350, 100, 55, (LPSTR)"arctan", hWnd, hGlobalHinstance, CC_BTN_ATN), WM_SETFONT, (WPARAM)hFuncFont, NULL);

	SendMessage(CreateButton(5, 410, 100, 55, (LPSTR)"csc", hWnd, hGlobalHinstance, CC_BTN_CSC), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(105, 410, 100, 55, (LPSTR)"sec", hWnd, hGlobalHinstance, CC_BTN_SEC), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(205, 410, 100, 55, (LPSTR)"cot", hWnd, hGlobalHinstance, CC_BTN_COT), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(304, 410, 100, 55, (LPSTR)"exp", hWnd, hGlobalHinstance, CC_BTN_EXP), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(405, 410, 100, 55, (LPSTR)"ln", hWnd, hGlobalHinstance, CC_BTN_LN), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(505, 410, 100, 55, (LPSTR)"lg", hWnd, hGlobalHinstance, CC_BTN_LOG), WM_SETFONT, (WPARAM)hFuncFont, NULL);

	SendMessage(CreateButton(5, 470, 100, 55, (LPSTR)"(", hWnd, hGlobalHinstance, CC_BTN_LQT), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(105, 470, 100, 55, (LPSTR)")", hWnd, hGlobalHinstance, CC_BTN_RQT), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(205, 470, 100, 55, (LPSTR)"π", hWnd, hGlobalHinstance, CC_BTN_PI), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(304, 470, 100, 55, (LPSTR)"e", hWnd, hGlobalHinstance, CC_BTN_E), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(405, 470, 100, 55, (LPSTR)"!", hWnd, hGlobalHinstance, CC_BTN_FCT), WM_SETFONT, (WPARAM)hFuncFont, NULL);
	SendMessage(CreateButton(505, 470, 100, 55, (LPSTR)"pow", hWnd, hGlobalHinstance, CC_BTN_POW), WM_SETFONT, (WPARAM)hFuncFont, NULL);
}

void HandleUserEvent(UINT uMsg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmd, int nShowCmd) {
	//保存程序实例句柄
	hGlobalHinstance = hInstance;
	//初始化一个窗口的基础信息
	WNDCLASS wndcls;
	wndcls.cbClsExtra = NULL;
	wndcls.cbWndExtra = NULL;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(RGB(255, 255, 255));
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
	SetRect(&rect, 0, 0, 935, 575);
	//AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	hGlobalMainHwnd = CreateWindow(
		"CustomerCalculator",
		"特色计算器",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		0, 0,
		(rect.right - rect.left), (rect.bottom - rect.top),
		NULL, NULL, hInstance, NULL
	);

	if (!hGlobalMainHwnd) {
		MessageBox(NULL, "窗口创建失败", "警告", MB_OK);
		return -2;
	}

	//创建计时器线程
	CreateThread(NULL, NULL, TimerProc, NULL, NULL, NULL);

	ShowWindow(hGlobalMainHwnd, SW_SHOWNORMAL);
	UpdateWindow(hGlobalMainHwnd);

	MessageLoop();

	return 0;
}

void MessageLoop() {
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return;
}

void InsertStr(char *opt) {
	//这个EM_REPLACESEL才是插入的=，=
	SendMessageA(hItems.hEdtMan.hwnd, EM_REPLACESEL, true, (long)opt);
}

void ClearAllEdit() {
	SetWindowTextA(hItems.hEdtMan.hwnd, "");
	SetWindowTextA(hItems.hEdtAns.hwnd, "");
}

void CalcAnswer() {
	char exp[2048];
	CalcError err = { 0 };
	GetWindowText(hItems.hEdtMan.hwnd, exp, 2047);
	double ans = calc(exp, 0, strlen(exp) - 1, &err);
	//检测错误
	if (err.err_code != 0) {
		//简单计算一下错误信息，这里会覆盖exp的内容，不过exp之后也用不到了，这里的exp[16] = 0是为了处理后面的strcat_s避免报错也为了安全
		exp[err.err_position + 15] = 0;
		try{
			strcat_s(err.err_msg, 16, exp + err.err_position);
		}
		catch (const std::exception&){
			strcat_s(err.err_msg, 16, "FATUL");
		}
		err.err_position++;
		char errstr[256] = { 0 };
		switch (err.err_code) {
		case ERR_FUNC_UNDEF:
			sprintf_s(errstr, 255, "使用了非法函数\r\n错误位置: %d\r\n错误表达式：%s", err.err_position, err.err_msg);
			break;
		case ERR_QOUT_OVFLW:
			sprintf_s(errstr, 255, "括号不匹配\r\n错误位置: %d\r\n错误表达式：%s", err.err_position, err.err_msg);
			break;
		case ERR_FUNC_EMPTY:
			sprintf_s(errstr, 255, "函数空值\r\n错误位置: %d\r\n错误表达式：%s", err.err_position, err.err_msg);
			break;
		case ERR_FUNC_OVFLW:
			sprintf_s(errstr, 255, "函数名过长，可能引起栈溢出\r\n错误位置: %d\r\n错误表达式：%s", err.err_position, err.err_msg);
			break;
		case ERR_NUM_BLANK:
			sprintf_s(errstr, 255, "计算符号后不应为空\r\n错误位置: %d\r\n错误表达式：%s", err.err_position, err.err_msg);
			break;
		case ERR_NUM_BUSY:
			sprintf_s(errstr, 255, "缺少运算符\r\n错误位置: %d\r\n错误表达式：%s", err.err_position, err.err_msg);
			break;
		case ERR_OPT_BUSY:
			sprintf_s(errstr, 255, "运算符前后应有参与计算的值\r\n错误位置: %d\r\n错误表达式：%s", err.err_position, err.err_msg);
			break;
		case ERR_EXPR_EXTRA:
			sprintf_s(errstr, 255, "计算式中包含非法字符\r\n错误位置: %d\r\n错误表达式：%s", err.err_position, err.err_msg);
			break;
		default:
			sprintf_s(errstr, 255, "未知错误\r\n错误位置: %d\r\n错误表达式：%s", err.err_position, err.err_msg);
			break;
		}
		SetWindowText(hItems.hEdtAns.hwnd, errstr);
		return;
	}
	std::string ans_str = std::to_string(ans);
	SetWindowText(hItems.hEdtAns.hwnd, ans_str.c_str());
}

void HandleUserEvent(UINT uMsg, WPARAM wp, LPARAM lp) {
	switch (LOWORD(wp)) {
	case CC_BTN_ADD:
		InsertStr((LPSTR)"+");
		break;
	case CC_BTN_SUB:
		InsertStr((LPSTR)"-");
		break;
	case CC_BTN_MUL:
		InsertStr((LPSTR)"*");
		break;
	case CC_BTN_DIV:
		InsertStr((LPSTR)"/");
		break;
	case CC_BTN_INV:
		InsertStr((LPSTR)"%");
		break;
	case CC_BTN_SIN:
		InsertStr((LPSTR)"sin()");
		break;
	case CC_BTN_COS:
		InsertStr((LPSTR)"cos()");
		break;
	case CC_BTN_TAN:
		InsertStr((LPSTR)"tan()");
		break;
	case CC_BTN_CSC:
		InsertStr((LPSTR)"csc()");
		break;
	case CC_BTN_SEC:
		InsertStr((LPSTR)"sec()");
		break;
	case CC_BTN_COT:
		InsertStr((LPSTR)"cot()");
		break;
	case CC_BTN_LOG:
		InsertStr((LPSTR)"lg()");
		break;
	case CC_BTN_LN:
		InsertStr((LPSTR)"ln()");
		break;
	case CC_BTN_EXP:
		InsertStr((LPSTR)"exp()");
		break;
	case CC_BTN_E:
		InsertStr((LPSTR)"e");
		break;
	case CC_BTN_PI:
		InsertStr((LPSTR)"PI");
		break;
	case CC_BTN_ASI:
		InsertStr((LPSTR)"arcsin()");
		break;
	case CC_BTN_ACS:
		InsertStr((LPSTR)"arccos()");
		break;
	case CC_BTN_ATN:
		InsertStr((LPSTR)"arctan()");
		break;
	case CC_BTN_FCT:
		InsertStr((LPSTR)"!");
		break;
	case CC_BTN_LQT:
		InsertStr((LPSTR)"(");
		break;
	case CC_BTN_RQT:
		InsertStr((LPSTR)")");
		break;
	case CC_BTN_CLS:
		ClearAllEdit();
		break;
	case CC_BTN_RUN:
		CalcAnswer();
		break;
	case CC_BTN_1:
		InsertStr((LPSTR)"1");
		break;
	case CC_BTN_2:
		InsertStr((LPSTR)"2");
		break;
	case CC_BTN_3:
		InsertStr((LPSTR)"3");
		break;
	case CC_BTN_4:
		InsertStr((LPSTR)"4");
		break;
	case CC_BTN_5:
		InsertStr((LPSTR)"5");
		break;
	case CC_BTN_6:
		InsertStr((LPSTR)"6");
		break;
	case CC_BTN_7:
		InsertStr((LPSTR)"7");
		break;
	case CC_BTN_8:
		InsertStr((LPSTR)"8");
		break;
	case CC_BTN_9:
		InsertStr((LPSTR)"9");
		break;
	case CC_BTN_0:
		InsertStr((LPSTR)"0");
		break;
	case CC_BTN_DOT:
		InsertStr((LPSTR)".");
		break;
	case CC_BTN_POW:
		InsertStr((LPSTR)"^");
		break;
	}
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) {
	static HFONT hFont;
	static HFONT hFuncFont, hAnsFont;

	switch (uMsg) {
	case WM_COMMAND:
		HandleUserEvent(uMsg, wp, lp);
		break;
	case WM_CREATE:
		hFont = CreateFont(-28, -14, 0, 0, 400, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, TEXT("微软雅黑"));
		hFuncFont = CreateFont(-20, -10, 0, 0, 300, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, TEXT("微软雅黑"));
		hAnsFont = CreateFont(-18, -9, 0, 0, 300, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, TEXT("微软雅黑"));
		hItems.hEdtMan.hwnd = CreateEditor(5, 5, 910, 150, hWnd, hGlobalHinstance, CC_EDT_MAIN, NULL);
		hItems.hEdtAns.hwnd = CreateEditor(5, 170, 600, 100, hWnd, hGlobalHinstance, CC_EDT_ANS, ES_READONLY);
		
		//创建按钮组
		CreateBtnGroup(hWnd, hFont, hFuncFont);

		//更改字体
		SendMessage(hItems.hEdtMan.hwnd, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hItems.hEdtAns.hwnd, WM_SETFONT, (WPARAM)hAnsFont, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		hGlobalMainHwnd = NULL;
		break;
	case WM_KEYDOWN:
		MessageBox(NULL, "w", "w", MB_OK);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}

DWORD WINAPI TimerProc(LPVOID lp) {
	while (hGlobalMainHwnd) {
		CalcAnswer();
		Sleep(TIMER_INTERVAL);
	}
	return NULL;
}