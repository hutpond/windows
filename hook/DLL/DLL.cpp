// DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include "stdio.h"
#include "Windows.h"
#include <atlstr.h>

HHOOK g_hHook = NULL;

CString IsNumber(WPARAM wParam)
{	
	CString message;	
	switch (wParam) 
	{	
	case 0x30:
		message.Format("����0"); 
		break;	
	case 0x31: 
		message.Format("����1"); 
		break;	
	case 0x32: 
		message.Format("����2"); 
		break;	
	case 0x33: 
		message.Format("����3"); 
		break;	
	case 0x34: 
		message.Format("����4"); 
		break;	
	case 0x35: 
		message.Format("����5"); 
		break;	
	case 0x36: 
		message.Format("����6"); 
		break;	
	case 0x37: 
		message.Format("����7"); 
		break;	
	case 0x38: 
		message.Format("����8"); 
		break;	
	case 0x39: 
		message.Format("����9"); 
		break;	
	default: 
		message.Format("δ����İ���"); 
		break;	
	}	
	return message;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PMSG   pMsg = (PMSG)lParam;
	PAINTSTRUCT ptstrt;
	RECT  rct;
	int   height, width;
	HWND   h_tWnd = FindWindow(NULL, "notepad");//Ҫ���ص�Ŀ�괰�� 

	if (h_tWnd != NULL && pMsg->hwnd == h_tWnd)
	{
		if (pMsg->message == WM_PAINT)
		{
			GetWindowRect(h_tWnd, &rct);
			height = rct.bottom - rct.top;
			width = rct.right - rct.left;
			HDC hdc = BeginPaint(h_tWnd, &ptstrt);
			for (int i = 20; i < width; i = i + 20)
			{
				MoveToEx(hdc, i, 0, 0);
				LineTo(hdc, i, height);
			}
			for (int j = 20; j < height; j = j + 20)
			{
				MoveToEx(hdc, 0, j, 0);
				LineTo(hdc, width, j);
			}

			EndPaint(h_tWnd, &ptstrt);

			return   1;
		}
		else
		{
			return   CallNextHookEx(g_hHook, nCode, wParam, lParam);
		}
	}
	else
	{
		return   CallNextHookEx(g_hHook, nCode, wParam, lParam);
	}
}
