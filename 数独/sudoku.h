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
	friend class BACKGROUND;
	INT x;
	INT y;
	HWND BTNWND;
	bool CLC = false;
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
private:
	HBITMAP CLCBitmap;
	HBITMAP UNCLCBitmap;
	HINSTANCE hInstance;
	HWND ParentWindow;
};
class BACKGROUND
{
public:
	void SetBitMap(INT bitmapID, HINSTANCE hInstance,INT BitmapW=500,INT BitmapH=500)
	{
		bitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(bitmapID));
		width = BitmapW;
		height = BitmapH;
		SendMessage(hStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);
		SetWindowPos(hStatic, HWND_DESKTOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	BACKGROUND(HWND hwnd, INT width= 500, INT height = 500)
	{
		hStatic = CreateWindow(WC_STATIC, NULL, SS_BITMAP | WS_CHILD | WS_VISIBLE, 0, 0, NULL, NULL, hwnd, NULL, GetModuleHandle(NULL), NULL);
	}
	~BACKGROUND()
	{
		DeleteBitmap(bitmap);
		DestroyWindow(hStatic);
	}
private:
	INT width;
	INT height;
	HWND hStatic;
	HBITMAP bitmap;
};
class ICON
{
public:
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
	HICON icon;
	NOTIFYICONDATA nid;
};