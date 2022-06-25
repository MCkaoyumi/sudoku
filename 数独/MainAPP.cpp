#include "resource.h"
#include "sudoku.h"
static TCHAR tip[] = _T("windowclass");
bool start = false, minizehide = false, windowhide = false, destroyicon = false,topmost=true;
HINSTANCE maininstance;
HBITMAP sudokumenu9, sudokumenu6, sudokumenu4, sudokumenuchecked;
HWND bmphwnd, windowwnd;
BITMAPBUTTON* play, * help, * backstart, * player, * count;
ICON* icon;
BACKGROUND* BG;
unsigned int mode;
void InitWindow(HWND hwnd)
{
	BG = new BACKGROUND(hwnd);
	BG->SetBitMap(IDB_BITMAP1, maininstance);
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
	play = new BITMAPBUTTON(160, 100, IDB_1CHECKED, IDB_1NOCHECKED, hwnd, maininstance, true);
	help = new BITMAPBUTTON(160, 200, IDB_2CHECKED, IDB_2NOCHECKED, hwnd, maininstance, true);
	backstart = new BITMAPBUTTON(160, 270, IDB_3CHECKED, IDB_3NOCHECKED, hwnd, maininstance, false);
	player = new BITMAPBUTTON(50, 120, IDB_4CHICKED, IDB_4NOCHICKED, hwnd, maininstance, false);
	count = new BITMAPBUTTON(250, 120, IDB_5CHICKED, IDB_5NOCHICKED, hwnd, maininstance, false);

}
void DeleteResource(void)
{
	delete play;
	delete help;
	delete backstart;
	delete player;
	delete count;
	delete icon;
	DeleteBitmap(sudokumenu9);
	DeleteBitmap(sudokumenu6);
	DeleteBitmap(sudokumenu4);
	DeleteBitmap(sudokumenuchecked);
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
				delete icon;
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
					delete icon;
				}
			}
			if (xx == ID_CLCEXIT)
			{
				DeleteResource();
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
		if (play->CLC)
		{
			play->HIDE();
			help->HIDE();
			player->SHOW();
			count->SHOW();
			BG->SetBitMap(IDB_WHICH, maininstance);
			break;
		}
		if (help->CLC)
		{
			play->HIDE();
			help->HIDE();
			backstart->SHOW();
			BG->SetBitMap(IDB_HELP, maininstance);
			break;
		}
		if (backstart->CLC)
		{
			backstart->HIDE();
			help->SHOW();
			play->SHOW();
			BG->SetBitMap(IDB_BITMAP1, maininstance);
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
			icon = new ICON(hwnd);
			windowhide = true;
			ShowWindow(hwnd, SW_HIDE);
			destroyicon = true;
			break;
		case ID_HIDE:
			if (CheckMenuItem(GetMenu(hwnd), ID_HIDE, MF_BYCOMMAND) == MF_UNCHECKED)
			{
				icon = new ICON(hwnd);
				CheckMenuItem(GetMenu(hwnd), ID_HIDE, MF_BYCOMMAND | MF_CHECKED);
				minizehide = true;
			}
			else
			{
				delete icon;
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
			DeleteResource();
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
			DeleteResource();
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
	wc.style = CS_HREDRAW | CS_VREDRAW;
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