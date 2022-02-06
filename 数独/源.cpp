#include "resource.h"
#include<Windows.h>
#include<windowsx.h>
#include<tchar.h>
#include<CommCtrl.h>
static TCHAR tip[] = _T("windowclass");
bool chicked1, chicked2;
HINSTANCE maininstance;
HBITMAP logo;
HBITMAP button1nochicked;
HBITMAP button1chicked;
HBITMAP button2nochicked;
HBITMAP button2chicked;
HBITMAP button3chicked;
HBITMAP button3nochicked;
HBITMAP help;
HWND bmphwnd;
HWND button1wnd;
HWND button2wnd;
HWND button3wnd;
LRESULT CALLBACK wndproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		if (chicked2)
		{
			SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)help);
			ShowWindow(button1wnd, SW_HIDE);
			ShowWindow(button2wnd, SW_HIDE);
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		int xpos, ypos;
		xpos = GET_X_LPARAM(lparam);
		ypos = GET_Y_LPARAM(lparam);
		if ((xpos < 324 && xpos>160) && (ypos > 100 && ypos < 184))
		{
			SendMessage(button1wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button1chicked);
			chicked1 = true;
		}
		else
		{ 
			SendMessage(button1wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button1nochicked);
			chicked1 = false;
		}	
		if ((xpos < 324 && xpos>160) && (ypos > 200 && ypos < 284))
		{
			SendMessage(button2wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button2chicked);
			chicked2 = true;
		}
		else
		{
			SendMessage(button2wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button2nochicked);
			chicked2 = false;
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))
		{
		case ID_EXIT:
			PostQuitMessage(2);
			break;
		default:
			break;
		}
		break;
	}
	case WM_CLOSE:
	{
		if (MessageBox(hwnd, _T("是否关闭"), _T("数独"), MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2) == 6)
			PostQuitMessage(1);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ncmdline, int pcmdshow)
{
	maininstance = hInstance;
	WNDCLASSEX wc={0};
	wc.cbSize = sizeof(wc);
	wc.lpszClassName = tip;
	wc.hbrBackground = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	wc.hInstance = hInstance;
	wc.lpfnWndProc = wndproc;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON2));
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, _T("注册窗口类失败"), _T("数独"), MB_OK | MB_ICONERROR);
		return -1;
	}
	HWND windowwnd=CreateWindow(tip, _T("数独"), WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, 500, 300, 500, 500, NULL, NULL, hInstance, NULL);
	SetWindowPos(windowwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	logo = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	button1nochicked = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_1NOCHICKED));
	button1chicked = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_1CHICKED));
	button2chicked= LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_2CHICKED));
	button2nochicked= LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_2NOCHICKED));
	help = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_HELP));
	bmphwnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 0, 0, 500, 500, windowwnd, NULL, hInstance, NULL);
	button1wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 160, 100, 164, 84, windowwnd, NULL, hInstance, NULL);
	button2wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 160, 200, 164, 84, windowwnd, NULL, hInstance, NULL);
	button3wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD, 160, 250, 164, 84, windowwnd, NULL, hInstance, NULL);
	SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)logo);
	SendMessage(button1wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button1nochicked);
	SendMessage(button2wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button2nochicked);
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}