#include "resource.h"
#include<Windows.h>
#include<windowsx.h>
#include<tchar.h>
#include<CommCtrl.h>
static TCHAR tip[] = _T("windowclass");
bool checked1, checked2,checked3;
bool home = true, back = false;
HINSTANCE maininstance;
HBITMAP logo, button1nochecked, button1checked, button2nochecked, button2checked, button3checked, button3nochecked, help;
HWND bmphwnd, button1wnd, button2wnd, button3wnd;
unsigned int mode;
INT_PTR WINAPI dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CLOSE:
		EndDialog(hwnd, 1);
	default:
		break;
	}
	return 0;
}
LRESULT CALLBACK wndproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		if (checked2)
		{
			SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)help);
			ShowWindow(button1wnd, SW_HIDE);
			ShowWindow(button2wnd, SW_HIDE);
			ShowWindow(button3wnd, SW_SHOW);
			home = false;
			back = true;
			checked2 = false;
			break;
		}
		if (checked3)
		{
			SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)logo);
			ShowWindow(button1wnd, SW_SHOW);
			ShowWindow(button2wnd, SW_SHOW);
			ShowWindow(button3wnd, SW_HIDE);
			home = true;
			back = false;
			checked3 = false;
			break;
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		int xpos, ypos;
		xpos = GET_X_LPARAM(lparam);
		ypos = GET_Y_LPARAM(lparam);
		if(home)
		{
			if ((xpos < 324 && xpos>160) && (ypos > 100 && ypos < 184))
			{
				SendMessage(button1wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button1checked);
				checked1 = true;
			}
			else
			{ 
				SendMessage(button1wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button1nochecked);
				checked1 = false;
			}	
			if ((xpos < 324 && xpos>160) && (ypos > 200 && ypos < 284))
			{
				SendMessage(button2wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button2checked);
				checked2 = true;
			}
			else
			{
				SendMessage(button2wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button2nochecked);
				checked2 = false;
			} 
		}
		if (back)
		{
			if ((xpos < 324 && xpos>160) && (ypos > 270 && ypos < 354))
			{
				SendMessage(button3wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button3checked);
				checked3 = true;
			}
			else
			{
				SendMessage(button3wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button3nochecked);
				checked3 = false;
			}
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))
		{
		case ID_4:
		{
			mode = 4;
			CheckMenuItem(GetMenu(hwnd), ID_4, MF_BYCOMMAND | MF_CHECKED);
			CheckMenuItem(GetMenu(hwnd), ID_6, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem(GetMenu(hwnd), ID_9, MF_BYCOMMAND | MF_UNCHECKED);
			break;
		}
		case ID_6:
		{
			mode = 6;
			CheckMenuItem(GetMenu(hwnd), ID_6, MF_BYCOMMAND | MF_CHECKED);
			CheckMenuItem(GetMenu(hwnd), ID_9, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem(GetMenu(hwnd), ID_4, MF_BYCOMMAND | MF_UNCHECKED);
			break;
		}
		case ID_9:
		{
			mode = 9;
			CheckMenuItem(GetMenu(hwnd), ID_9, MF_BYCOMMAND | MF_CHECKED);
			CheckMenuItem(GetMenu(hwnd), ID_6, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem(GetMenu(hwnd), ID_4, MF_BYCOMMAND | MF_UNCHECKED);
			break;
		}
		case ID_ABOUT:
			DialogBox(maininstance, MAKEINTRESOURCE(IDD_DLGABOUT), hwnd, dlgproc);
			break;
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
	button1nochecked = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_1NOCHECKED));
	button1checked = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_1CHECKED));
	button2checked= LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_2CHECKED));
	button2nochecked= LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_2NOCHECKED));
	button3checked = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_3CHECKED));
	button3nochecked = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_3NOCHECKED));
	help = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_HELP));
	bmphwnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 0, 0, 500, 500, windowwnd, NULL, hInstance, NULL);
	button1wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 160, 100, 164, 84, windowwnd, NULL, hInstance, NULL);
	button2wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 160, 200, 164, 84, windowwnd, NULL, hInstance, NULL);
	button3wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD, 160, 270, 164, 84, windowwnd, NULL, hInstance, NULL);
	SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)logo);
	SendMessage(button1wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button1nochecked);
	SendMessage(button2wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button2nochecked);
	SendMessage(button3wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button3nochecked);
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}