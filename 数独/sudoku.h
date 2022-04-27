#pragma once
#include<Windows.h>
#include<windowsx.h>
#include<CommCtrl.h>
#include<tchar.h>
#include<thread>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define IDR_MAINFRAME 2021
#define WM_TO_TRAY 114514
class BITMAPBUTTON
{
public:	
	INT x;
	INT y;
	HWND BTNWND;
	HWND ParentWindow;
	bool CLC = false;
	HBITMAP CLCBitmap;
	HBITMAP UNCLCBitmap;
	HINSTANCE hInstance;
	bool Show;
	BITMAPBUTTON(INT x, INT y, INT CLCBitmapID, INT UNCLCBitmapID, HWND hwnd, HINSTANCE hInstance, bool SHOW)
	{
		this->x = x;
		this->y = y;
		this->hInstance = hInstance;
		Show = SHOW;
		ParentWindow = hwnd;
		CLCBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(CLCBitmapID));
		UNCLCBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(UNCLCBitmapID));
		BTNWND = CreateWindow(WC_STATIC, NULL, SS_BITMAP | WS_CHILD , x, y, NULL, NULL, hwnd, NULL, hInstance, NULL);
		SendMessage(BTNWND, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)UNCLCBitmap);
		if (SHOW)
			ShowWindow(BTNWND, SW_SHOW);
	}
	~BITMAPBUTTON()
	{
		DeleteBitmap(CLCBitmap);
		DeleteBitmap(UNCLCBitmap);
	}

	void CheckedButton(void)
	{
		if(Show)
		{ 
		POINT Mousepos;
		GetCursorPos(&Mousepos);
		RECT rect;
		GetWindowRect(BTNWND, &rect);
		if (Mousepos.x > rect.left && Mousepos.x<rect.right && Mousepos.y>rect.top && Mousepos.y < rect.bottom)
		{
			SendMessage(BTNWND, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)CLCBitmap);
			if (!CLC)
				PlaySound(MAKEINTRESOURCE(IDR_WAVE1),hInstance, SND_RESOURCE | SND_ASYNC);
			CLC = true;
		}
		else
		{
			SendMessage(BTNWND, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)UNCLCBitmap);
			CLC = false;
		}
		}
		UpdateWindow(ParentWindow);
	}
	void HIDE(void)
	{
		ShowWindow(BTNWND, SW_HIDE);
		Show = false;
		CLC = false;
	}
	void SHOW(void)
	{
		ShowWindow(BTNWND, SW_SHOW);
		Show = true;
		CLC = false;
	}
};
class ICON
{
public:
	HICON icon;
	ICON(HWND hwnd, HICON icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)))
	{
		this->icon = icon;
		nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
		nid.hWnd = hwnd;
		nid.uID = IDR_MAINFRAME;
		nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = WM_TO_TRAY;
		nid.hIcon = icon;
		wcscpy_s(nid.szTip, _T("Êý¶À"));
		Shell_NotifyIcon(NIM_ADD, &nid);
	}
	~ICON()
	{
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
private:
	NOTIFYICONDATA nid;
};