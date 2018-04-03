//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "frmmain.h"
#pragma hdrstop

#pragma argsused

long WINAPI MainThread(long lParam)
{
	WaitForInputIdle((void*)-1, 10000);
	Application->CreateForm(__classid(TForm1),&Form1);
	Application->Run();
	Application->ProcessMessages();
	return 1;
}

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
		CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)MainThread,NULL,0,0);
		break;
		case DLL_PROCESS_DETACH:
		//ExitProcess(1);
		break;
	}
	return 1;
}
//---------------------------------------------------------------------------
