#include "resource.h"
#include<Windows.h>
#include<windowsx.h>
#include<tchar.h>
#include<CommCtrl.h>
#include<iostream>
#include<thread>
#include "mmsystem.h"
#include<thread>
#pragma comment(lib, "winmm.lib")
#define IDR_MAINFRAME 2021
#define WM_TO_TRAY 114514
static TCHAR tip[] = _T("windowclass");
bool checked1, checked2,checked3,checked4,checked5;
bool home = true, back1 = false, back2 = false, start = false, minizehide = false, windowhide = false, destroyicon = false;
HINSTANCE maininstance;
HBITMAP logo, button1nochecked, button1checked, button2nochecked, button2checked, button3checked, button3nochecked,button4nochecked, button4checked, button5checked, button5nochecked, help,which,sudokumenu9, sudokumenu6, sudokumenu4, sudokumenuchecked;
HWND bmphwnd, button1wnd, button2wnd, button3wnd,button4wnd,button5wnd,windowwnd;
unsigned int mode;
void showicon(HWND hwnd)
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_TO_TRAY;
	nid.hIcon = LoadIcon(maininstance, MAKEINTRESOURCE(IDI_ICON1));
	wcscpy_s(nid.szTip, _T("数独"));
	Shell_NotifyIcon(NIM_ADD, &nid);
}
void deleteicon(HWND hwnd)
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_TO_TRAY;
	nid.hIcon = LoadIcon(maininstance, MAKEINTRESOURCE(IDI_ICON1));
	wcscpy_s(nid.szTip, _T("数独"));
	Shell_NotifyIcon(NIM_DELETE, &nid);
}
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
	POINT pt;
	int xx;
	switch (msg)
	{
	case WM_TO_TRAY:
		if (windowhide && lparam == WM_LBUTTONDOWN)
		{
			windowhide = false;
			SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
			ShowWindow(hwnd, SW_RESTORE);
			if (destroyicon && !minizehide)
			{
				destroyicon = false;
				deleteicon(hwnd);
			}
		}
		if (lparam == WM_RBUTTONDOWN)
		{
			HMENU hmenu = CreatePopupMenu();
			AppendMenu(hmenu, MF_STRING, ID_SHOW, L"显示");
			AppendMenu(hmenu, MF_SEPARATOR, NULL, NULL); 
			AppendMenu(hmenu, MF_STRING, ID_CLCEXIT, L"退出");
			GetCursorPos(&pt);
			SetForegroundWindow(hwnd);
			if (!windowhide)
				EnableMenuItem(hmenu, ID_SHOW, MF_BYCOMMAND | MF_GRAYED);
			else
				EnableMenuItem(hmenu, ID_SHOW, MF_BYCOMMAND | MF_ENABLED);
			xx = TrackPopupMenu(hmenu, TPM_RETURNCMD, pt.x, pt.y, NULL, hwnd, NULL);
			if (xx == ID_SHOW)
			{
				windowhide = false;
				SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
				ShowWindow(hwnd, SW_RESTORE);
				if (destroyicon && !minizehide)
				{
					destroyicon = false;
					deleteicon(hwnd);
				}
			}
			if (xx == ID_CLCEXIT)
			{
				DeleteBitmap(logo);
				DeleteBitmap(button1nochecked);
				DeleteBitmap(button1checked);
				DeleteBitmap(button2nochecked);
				DeleteBitmap(button2checked);
				DeleteBitmap(button3checked);
				DeleteBitmap(button3nochecked);
				DeleteBitmap(button4nochecked);
				DeleteBitmap(button4checked);
				DeleteBitmap(button5checked);
				DeleteBitmap(button5nochecked);
				DeleteBitmap(help);
				DeleteBitmap(which);
				DeleteBitmap(sudokumenu9);
				DeleteBitmap(sudokumenu6);
				DeleteBitmap(sudokumenu4);
				DeleteBitmap(sudokumenuchecked);
				deleteicon(hwnd);
				PostQuitMessage(3);
			}
		}
		break;
	case WM_SIZE:
		if (wparam == SIZE_MINIMIZED && minizehide)
		{
			windowhide = true;
			ShowWindow(hwnd, SW_HIDE);
		}
		break;
	case WM_CREATE:
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		which = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_WHICH));
		logo = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_BITMAP1));
		button1nochecked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_1NOCHECKED));
		button1checked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_1CHECKED));
		button2checked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_2CHECKED));
		button2nochecked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_2NOCHECKED));
		button3checked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_3CHECKED));
		button3nochecked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_3NOCHECKED));
		button4checked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_4CHICKED));
		button4nochecked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_4NOCHICKED));
		button5checked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_5CHICKED));
		button5nochecked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_5NOCHICKED));
		help = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_HELP));
		bmphwnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 0, 0, 500, 500, hwnd, NULL, maininstance, NULL);
		button1wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 160, 100, 164, 84, hwnd, NULL, maininstance, NULL);
		button2wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 160, 200, 164, 84, hwnd, NULL, maininstance, NULL);
		button3wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD, 160, 270, 164, 84, hwnd, NULL, maininstance, NULL);
		button4wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD, 50, 120, 164, 84, hwnd, NULL, maininstance, NULL);
		button5wnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD, 250, 120, 164, 84, hwnd, NULL, maininstance, NULL);
		SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)logo);
		SendMessage(button1wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button1nochecked);
		SendMessage(button2wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button2nochecked);
		SendMessage(button3wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button3nochecked);
		SendMessage(button4wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button4nochecked);
		SendMessage(button5wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button5nochecked);
		sudokumenuchecked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_MENUCHECKED));
		sudokumenu9 = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_9));
		sudokumenu6 = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_6));
		sudokumenu4 = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_4));
		SetMenuItemBitmaps(GetMenu(hwnd), ID_9, MF_BYCOMMAND, sudokumenu9, sudokumenuchecked);
		SetMenuItemBitmaps(GetMenu(hwnd), ID_6, MF_BYCOMMAND, sudokumenu6, sudokumenuchecked);
		SetMenuItemBitmaps(GetMenu(hwnd), ID_4, MF_BYCOMMAND, sudokumenu4, sudokumenuchecked);
		DrawMenuBar(hwnd);
		break;
	case WM_LBUTTONDOWN:
	{
		if (checked1)
		{
			SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)which);
			ShowWindow(button1wnd, SW_HIDE);
			ShowWindow(button2wnd, SW_HIDE);
			ShowWindow(button4wnd, SW_SHOW);
			ShowWindow(button5wnd, SW_SHOW);
			home = false;
			back2 = true;
			checked1 = false;
			break;
		}
		if (checked2)
		{
			SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)help);
			ShowWindow(button1wnd, SW_HIDE);
			ShowWindow(button2wnd, SW_HIDE);
			ShowWindow(button3wnd, SW_SHOW);
			home = false;
			back1 = true;
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
			back1 = false;
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
				if (!checked1)
					PlaySound(MAKEINTRESOURCE(IDR_WAVE1), maininstance, SND_RESOURCE | SND_ASYNC);
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
				if (!checked2)
					PlaySound(MAKEINTRESOURCE(IDR_WAVE1), maininstance, SND_RESOURCE | SND_ASYNC);
				checked2 = true;
			}
			else
			{
				SendMessage(button2wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button2nochecked);
				checked2 = false;
			} 
		}
		if (back1)
		{
			if ((xpos < 324 && xpos>160) && (ypos > 270 && ypos < 354))
			{
				SendMessage(button3wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button3checked);
				if (!checked3)
					PlaySound(MAKEINTRESOURCE(IDR_WAVE1), maininstance, SND_RESOURCE | SND_ASYNC);
				checked3 = true;
			}
			else
			{
				SendMessage(button3wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button3nochecked);
				checked3 = false;
			}
		}
		if (back2)
		{
			if ((xpos < 214 && xpos>50) && (ypos > 120 && ypos < 204))
			{
				SendMessage(button4wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button4checked);
				if (!checked4)
					PlaySound(MAKEINTRESOURCE(IDR_WAVE1), maininstance, SND_RESOURCE | SND_ASYNC);
				checked4 = true;
			}
			else
			{
				SendMessage(button4wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button4nochecked);
				checked4 = false;
			}
			if ((xpos < 414 && xpos>250) && (ypos > 120 && ypos < 204))
			{
				SendMessage(button5wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button5checked);
				if (!checked5)
					PlaySound(MAKEINTRESOURCE(IDR_WAVE1), maininstance, SND_RESOURCE | SND_ASYNC);
				checked5 = true;
			}
			else
			{
				SendMessage(button5wnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)button5nochecked);
				checked5 = false;
			}
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))
		{
		case ID_SOONHIDE:
			showicon(hwnd);
			windowhide = true;
			ShowWindow(hwnd, SW_HIDE);
			destroyicon = true;
			break;
		case ID_HIDE:
			if (CheckMenuItem(GetMenu(hwnd), ID_HIDE, MF_BYCOMMAND) == MF_UNCHECKED)
			{
				showicon(hwnd);
				CheckMenuItem(GetMenu(hwnd), ID_HIDE, MF_BYCOMMAND | MF_CHECKED);
				minizehide = true;
			}
			else
			{
				deleteicon(hwnd);
				CheckMenuItem(GetMenu(hwnd), ID_HIDE, MF_BYCOMMAND | MF_UNCHECKED);
				minizehide = false;
			}
			break;
		case ID_4:
		{
			mode = 4;
			CheckMenuRadioItem(GetMenu(hwnd), ID_9, ID_4, ID_4, MF_BYCOMMAND);
			break;
		}
		case ID_6:
		{
			mode = 6;
			CheckMenuRadioItem(GetMenu(hwnd), ID_9, ID_4, ID_6, MF_BYCOMMAND);
			break;
		}
		case ID_9:
		{
			mode = 9;
			CheckMenuRadioItem(GetMenu(hwnd), ID_9, ID_4, ID_9, MF_BYCOMMAND);
			break;
		}
		case ID_ABOUT:
			DialogBox(maininstance, MAKEINTRESOURCE(IDD_DLGABOUT), hwnd, dlgproc);
			break;
		case ID_EXIT:
			DeleteBitmap(logo);
			DeleteBitmap(button1nochecked);
			DeleteBitmap(button1checked);
			DeleteBitmap(button2nochecked);
			DeleteBitmap(button2checked);
			DeleteBitmap(button3checked);
			DeleteBitmap(button3nochecked);
			DeleteBitmap(button4nochecked);
			DeleteBitmap(button4checked);
			DeleteBitmap(button5checked);
			DeleteBitmap(button5nochecked);
			DeleteBitmap(help);
			DeleteBitmap(which);
			DeleteBitmap(sudokumenu9);
			DeleteBitmap(sudokumenu6);
			DeleteBitmap(sudokumenu4);
			DeleteBitmap(sudokumenuchecked);
			deleteicon(hwnd);
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
		{
			DeleteBitmap(logo);
			DeleteBitmap(button1nochecked);
			DeleteBitmap(button1checked);
			DeleteBitmap(button2nochecked);
			DeleteBitmap(button2checked);
			DeleteBitmap(button3checked);
			DeleteBitmap(button3nochecked);
			DeleteBitmap(button4nochecked);
			DeleteBitmap(button4checked);
			DeleteBitmap(button5checked);
			DeleteBitmap(button5nochecked);
			DeleteBitmap(help);
			DeleteBitmap(which);
			DeleteBitmap(sudokumenu9);
			DeleteBitmap(sudokumenu6);
			DeleteBitmap(sudokumenu4);
			DeleteBitmap(sudokumenuchecked);
			deleteicon(hwnd);
			PostQuitMessage(1);
		}
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
	windowwnd=CreateWindow(tip, _T("数独"), WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, 500, 300, 500, 500, NULL, NULL, hInstance, NULL);
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}