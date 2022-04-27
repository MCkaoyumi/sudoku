#include "resource.h"
#include "sudoku.h"
static TCHAR tip[] = _T("windowclass");
bool start = false, minizehide = false, windowhide = false, destroyicon = false,topmost=true;
HINSTANCE maininstance;
HBITMAP logo, helpb, which, sudokumenu9, sudokumenu6, sudokumenu4, sudokumenuchecked;
HWND bmphwnd, windowwnd;
BITMAPBUTTON* play, * help, * backstart, * player, * count;
unsigned int mode;
HBITMAP png;
void InitWindow(HWND hwnd)
{
	play = new BITMAPBUTTON(160, 100, IDB_1CHECKED, IDB_1NOCHECKED, hwnd, maininstance, true);
	help = new BITMAPBUTTON(160, 200, IDB_2CHECKED, IDB_2NOCHECKED, hwnd, maininstance, true);
	backstart = new BITMAPBUTTON(160, 270, IDB_3CHECKED, IDB_3NOCHECKED, hwnd, maininstance, false);
	player = new BITMAPBUTTON(50, 120, IDB_4CHICKED, IDB_4NOCHICKED, hwnd, maininstance, false);
	count = new BITMAPBUTTON(250, 120, IDB_5CHICKED, IDB_5NOCHICKED, hwnd, maininstance, false);
	which = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_WHICH));
	logo = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_BITMAP1));
	helpb = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_HELP));
	bmphwnd = CreateWindow(WC_STATIC, NULL, SS_BITMAP | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, 0, 0, 500, 500, hwnd, NULL, maininstance, NULL);
	SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)logo);
	sudokumenuchecked = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_MENUCHECKED));
	sudokumenu9 = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_9));
	sudokumenu6 = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_6));
	sudokumenu4 = LoadBitmap(maininstance, MAKEINTRESOURCE(IDB_4));
	SetMenuItemBitmaps(GetMenu(hwnd), ID_9, MF_BYCOMMAND, sudokumenu9, sudokumenuchecked);
	SetMenuItemBitmaps(GetMenu(hwnd), ID_6, MF_BYCOMMAND, sudokumenu6, sudokumenuchecked);
	SetMenuItemBitmaps(GetMenu(hwnd), ID_4, MF_BYCOMMAND, sudokumenu4, sudokumenuchecked);
	CheckMenuItem(GetMenu(hwnd), ID_TOPMOST, MF_BYCOMMAND | MF_CHECKED);
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	DrawMenuBar(hwnd);
}
void DeleteBitmaps(void)
{
	delete play;
	delete help;
	delete backstart;
	delete player;
	delete count;
	DeleteBitmap(logo);
	DeleteBitmap(help);
	DeleteBitmap(which);
	DeleteBitmap(sudokumenu9);
	DeleteBitmap(sudokumenu6);
	DeleteBitmap(sudokumenu4);
	DeleteBitmap(sudokumenuchecked);
}
bool clcchecked(HWND HButton)
{
	POINT Mousepos;
	GetCursorPos(&Mousepos);
	RECT rect;
	GetWindowRect(HButton, &rect);
	return Mousepos.x > rect.left && Mousepos.x<rect.right&& Mousepos.y>rect.top && Mousepos.y < rect.bottom ? true : false;
}
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
			if(topmost)
				SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
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
				if(topmost)
					SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				ShowWindow(hwnd, SW_RESTORE);
				if (destroyicon && !minizehide)
				{
					destroyicon = false;
					deleteicon(hwnd);
				}
			}
			if (xx == ID_CLCEXIT)
			{
				DeleteBitmaps();
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
		InitWindow(hwnd);
		break;
	case WM_LBUTTONDOWN:
	{
		UpdateWindow(hwnd);
		if (play->CLC)
		{
			SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)which);
			play->HIDE();
			help->HIDE();
			player->SHOW();
			count->SHOW();
			break;
		}
		if (help->CLC)
		{
			SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)helpb);
			play->HIDE();
			help->HIDE();
			backstart->SHOW();
			break;
		}
		if (backstart->CLC)
		{
			SendMessage(bmphwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)logo);
			backstart->HIDE();
			play->SHOW();
			help->SHOW();
			break;
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		play->CheckedButton();
		help->CheckedButton();
		backstart->CheckedButton();
		player->CheckedButton();
		count->CheckedButton();
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))
		{
		case ID_TOPMOST:
			if (CheckMenuItem(GetMenu(hwnd), ID_TOPMOST, MF_BYCOMMAND) == MF_CHECKED)
			{
				CheckMenuItem(GetMenu(hwnd), ID_TOPMOST, MF_BYCOMMAND | MF_UNCHECKED);
				SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
				topmost = false;
			}
			else
			{
				CheckMenuItem(GetMenu(hwnd), ID_TOPMOST, MF_BYCOMMAND | MF_CHECKED);
				SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
				topmost = true;
			}
			break;
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
			DeleteBitmaps();
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
			DeleteBitmaps();
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