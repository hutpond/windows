// CPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

//#include "stdafx.h"
#include "windows.h"
#include "Psapi.h"
#include <atlstr.h>

#pragma comment(lib,"Psapi.lib")

DWORD FindProcessByEnumProcess(CString TargetProcessName)
{	
	DWORD TargetProcessId = 0;
	DWORD ProcessesId[1024] = { 0 }; 
	DWORD NeededProcessesId = 0; 
	LPSTR ProcessName = (LPSTR)malloc((sizeof(char)) * 1024);	
	EnumProcesses(ProcessesId, sizeof(ProcessesId), &NeededProcessesId);	
	DWORD ProcessNumber = NeededProcessesId / sizeof(DWORD);	

	for (unsigned int i = 0; i < ProcessNumber; i++)	
	{		
		if (ProcessesId[i] != 0)		
		{			
			HANDLE hProcess = OpenProcess(
				PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessesId[i]);			

			if (hProcess != NULL)			
			{				
				GetModuleFileNameEx(hProcess, NULL, ProcessName, 1024);
				CString ProcessFullPathName = (CString)ProcessName;				
				CString ProcessBaseName = ProcessFullPathName.Right(
					ProcessFullPathName.GetLength() - \
					ProcessFullPathName.ReverseFind('\\') - 1
				);				
				if (ProcessBaseName == TargetProcessName)
				{					
					TargetProcessId = ProcessesId[i];				
				}				
				CloseHandle(hProcess);//�رվ��				
				hProcess = NULL;			
			}		
		}	
	} 	
	return TargetProcessId;
} 

void DoInject(DWORD TargetWindowThreadId)
{	
	HMODULE hDll = LoadLibrary(_T("DLL.dll"));	
	if (hDll == NULL) 
	{		
		printf("��dll���ص��������ʧ��\n");		
		exit(0);	
	}	
	else 
	{		
		printf("��dll���ص�������̳ɹ�\n");	
	}

	FARPROC KeyboardProc = (FARPROC)GetProcAddress(hDll, "KeyboardProc");	
	if (KeyboardProc == NULL) 
	{		
		printf("��ȡ���ص�������ַʧ��\n");		
		exit(0);	
	}	
	else 
	{		
		printf("��ȡ���ص�������ַ�ɹ�\n");	
	}

	//HHOOK g_hHook = SetWindowsHookEx(
	//	WH_KEYBOARD, (HOOKPROC)KeyboardProc, hDll, TargetWindowThreadId);	
	HHOOK g_hHook = SetWindowsHookEx(
		WH_GETMESSAGE, (HOOKPROC)KeyboardProc, hDll, TargetWindowThreadId);
	if (g_hHook)
	{		
		printf("��Ŀ���߳���ӹ��Ӳ�ע��dll�ɹ�\n");	
	} 	
	printf("����qж�ع��ӣ�");	
	while (getchar() != 'q'); 	
	if (g_hHook)	
	{		
		UnhookWindowsHookEx(g_hHook);		
		g_hHook = NULL;	
	}	
	FreeLibrary(hDll);
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{	
	DWORD CurrentWindowProcessId;
	DWORD CurrentWindowThreadId;
	CurrentWindowThreadId = GetWindowThreadProcessId(hwnd, &CurrentWindowProcessId);	
	if (CurrentWindowProcessId == lParam) 
	{		
		DoInject(CurrentWindowThreadId);		
		return false; 
	} 	
	return true; 
} 

int main()
{	
	CString TargetProcessName(_T("notepad.exe"));	
	DWORD TargetProcessId = FindProcessByEnumProcess(TargetProcessName); 
	EnumWindows(EnumWindowsProc, TargetProcessId);
}

