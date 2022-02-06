#include "resource.h"
#include<Windows.h>
#include<windowsx.h>
#include<tchar.h>
static TCHAR tip[] = _T("windowclass");
HINSTANCE maininstance;
HBITMAP logo;
HBITMAP button1nochicked;
HBITMAP button1chicked;
HBITMAP button2nochicked;
HBITMAP button2chicked;
HWND bmphwnd;
HWND button1wnd;
HWND button2wnd;
LRESULT CALLBACK wndproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
	{
		int xpos, ypos;
		xpos = GET_X_LPARAM(lparam);
		ypos = GET_Y_LPARAM(lparam);
		if ((xpos < 324 && xpos>160) && (ypos > 100 && ypos < 190))
			SendMessage(button1wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button1chicked);
		else
			SendMessage(button1wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button1nochicked);
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
	HWND windowwnd=CreateWindow(tip, _T("数独"), WS_CAPTION | WS_POPUPWINDOW, 500, 300, 500, 500, NULL, NULL, hInstance, NULL);
	SetWindowPos(windowwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	ShowWindow(windowwnd, SW_SHOW);
	logo = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_BITMAP1));
	button1nochicked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_1NOCHICKED));
	button1chicked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_1CHICKED));
	bmphwnd = CreateWindow(TEXT("STATIC"), NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 0, 0, 500, 500, windowwnd, NULL, (HINSTANCE)GetWindowLongPtr(windowwnd, GWLP_HINSTANCE), NULL);
	button1wnd = CreateWindow(_T("STATIC"), NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 160, 100, 164, 84, windowwnd, NULL, (HINSTANCE)GetWindowLongPtr(windowwnd, GWLP_HINSTANCE), NULL);
	SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)logo);
	SendMessage(button1wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button1nochicked);
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}