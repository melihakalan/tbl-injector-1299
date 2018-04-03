//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form.h"
#include "windows.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void acmetest(PROCESS_INFORMATION pi)
{
	ResumeThread(pi.hThread);
	BYTE r = 0;
	while(r != 0xE9)
	{
		ReadProcessMemory(pi.hProcess,(void*)0x676219,&r,1,0);
	}
	SuspendThread(pi.hThread);

//	BYTE ptest[] = {0x68,0xE1,0x65,0x44,0x00,0xC3};
//	WriteProcessMemory(pi.hProcess,(void*)0x4465d2,ptest,6,0);

	//MessageBoxA(Form1->Handle,"asdasd",0,0);
	Sleep(100);

	DWORD dw1 = (DWORD)GetProcAddress(GetModuleHandle("kernel32.dll"),"GetCommandLineA");
	WriteProcessMemory(pi.hProcess,(void*)0x6A3194,&dw1,4,0);
	BYTE p1[] = {0xff,0x15,0x94,0x31,0x6a,0x0};
	WriteProcessMemory(pi.hProcess,(void*)0x67629f,p1,6,0);

	DWORD dw2 = (DWORD)GetProcAddress(GetModuleHandle("kernel32.dll"),"GetVersion");
	WriteProcessMemory(pi.hProcess,(void*)0x6A3190,&dw2,4,0);
	BYTE p2[] = {0xff,0x15,0x90,0x31,0x6a,0x0};
	WriteProcessMemory(pi.hProcess,(void*)0x67623f,p2,6,0);

	DWORD dw3 = (DWORD)GetProcAddress(GetModuleHandle("kernel32.dll"),"GetStartupInfoA");
	WriteProcessMemory(pi.hProcess,(void*)0x6A3198,&dw3,4,0);
	BYTE p3[] = {0xff,0x15,0x98,0x31,0x6a,0x0};
	WriteProcessMemory(pi.hProcess,(void*)0x6762ca,p3,6,0);

	DWORD dw4 = (DWORD)GetProcAddress(GetModuleHandle("kernel32.dll"),"GetModuleHandleA");
	WriteProcessMemory(pi.hProcess,(void*)0x6A31EC,&dw4,4,0);
	BYTE p4[] = {0xff,0x15,0xec,0x31,0x6a,0x0};
	WriteProcessMemory(pi.hProcess,(void*)0x6762ed,p4,6,0);
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	char pid[8]={0};    *pid = ' ';  		// 1234
	itoa(GetCurrentProcessId(),pid+1,10);

	for(int i = 1; i <= strlen((char*)(pid+1)); i++)
	{
		*(pid+i) = *(pid+i)+1;
	}

	char cmd[256] = {0};
	*cmd = 0x22;
	strcpy((cmd+1),GetCurrentDir().c_str());
	strcat(cmd,"\\KnightOnline.exe");
	int len = strlen(cmd);
	*(cmd + len) = 0x22;
	strcat(cmd," ");
	strcat(cmd,pid);

	CreateProcess("KnightOnline.exe",cmd,NULL,NULL,true,NULL,NULL,GetCurrentDir().c_str(),&si,&pi);
	SuspendThread(pi.hThread);

	Sleep(100);

	acmetest(pi);

	HMODULE hKernel32 = GetModuleHandle("kernel32.dll");
	FARPROC hLoadLibrary = GetProcAddress(hKernel32, "LoadLibraryA");

	int iMemSize = strlen("kojd_tbl.dll") + 1;

	LPVOID lpVirtualMem = VirtualAllocEx(pi.hProcess, NULL, iMemSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if(!lpVirtualMem){
		MessageBox(0,"Hafiza acilamadi!","Hata",MB_ICONEXCLAMATION);
		TerminateProcess(pi.hProcess,0);
		return;
	}

	WriteProcessMemory(pi.hProcess,lpVirtualMem,"kojd_tbl.dll",iMemSize - 1,NULL);
	HANDLE hBotThread = CreateRemoteThread(pi.hProcess,NULL,NULL,(LPTHREAD_START_ROUTINE)hLoadLibrary,lpVirtualMem,NULL,NULL);

	CloseHandle(hBotThread);
	VirtualFreeEx(pi.hProcess, lpVirtualMem, iMemSize, MEM_RELEASE);

	ResumeThread(pi.hThread);

	WaitForInputIdle(pi.hProcess,INFINITE);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	Application->Terminate();
}
//---------------------------------------------------------------------------
