//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmmain.h"
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

long __stdcall newstdstring(char* cstr)
{
	long mstd = (long)malloc(256);	//simdilik yeter
	if(!mstd)	return 0;
	memset((void*)mstd,0,256);

	char* _cstr = cstr;
	int len = strlen(cstr);
	asm
	{
		mov ecx,mstd
		push len
		push _cstr
		mov eax,0x4083A0
		call eax
	}
	return mstd;
}

void inject_skillmain()
{
	//	kojd (melih)
	//	ko tbl inject
	//	yeni bir class için malloc alýyorum,
	//	eskisinin yerine yazýyorum,
	//	yeni dosyayý çözerek içerisini dolduruyorum...

	long tblbase = (long)malloc(0x24); memset((void*)tblbase,0,0x24);
	long arg1 = 0, arg2 = 0, arg3 = 0;
	DWORD dwSizeHigh = 0, dwSizeLow = 0, dwReaded = 0;
	long stdname = newstdstring("injectlist\\Skill_Magic_Main_us.tbl");

	asm
	{
		lea eax,&arg1
		mov ecx,tblbase
		add ecx,4
		push eax
		mov eax,0x590890
		call eax

		lea ecx,&arg2
		lea edx,&arg3
		mov eax,tblbase
		add eax,0x14
		push ecx
		push edx
		mov ecx,eax
		mov eax,0x61D110
		call eax

		mov eax,tblbase
		mov [eax],0x6A9844
		mov [0x818760],eax

		mov ecx,eax
		push stdname
		mov eax,0x617380
		call eax
	}
	free((void*)stdname);
}

void inject_skill4()
{

  // gameprocmain + 0x18c + 0x28

	long tblbase = (long)malloc(0x24); memset((void*)tblbase,0,0x24);
	long arg1 = 0, arg2 = 0, arg3 = 0;
	DWORD dwSizeHigh = 0, dwSizeLow = 0, dwReaded = 0;
	long stdname = newstdstring("injectlist\\skill_magic_4.tbl");

	asm
	{
		lea eax,&arg1
		mov ecx,tblbase
		add ecx,4
		push eax
		mov eax,0x590890
		call eax

		lea ecx,&arg2
		lea edx,&arg3
		mov eax,tblbase
		add eax,0x14
		push ecx
		push edx
		mov ecx,eax
		mov eax,0x5908B0
		call eax

		mov eax,tblbase
		mov [eax],0x6A82AC
		mov ecx,[0x8189B8]	//dlga
		mov ecx,[ecx + 0x18C]
		mov [ecx + 0x28], eax

		mov ecx,eax
		push stdname
		mov eax,0x58DE70
		call eax
	}
	free((void*)stdname);
}

void inject_itemorg()
{
	// 0x8186F4	1299

	//	kojd (melih)
	//	ko tbl inject
	//	yeni bir class için malloc alýyorum,
	//	eskisinin yerine yazýyorum,
	//	yeni dosyayý çözerek içerisini dolduruyorum...

	long tblbase = (long)malloc(0x24); memset((void*)tblbase,0,0x24);
	long arg1 = 0, arg2 = 0, arg3 = 0;
	DWORD dwSizeHigh = 0, dwSizeLow = 0, dwReaded = 0;

	asm
	{
		lea eax,&arg1
		mov ecx,tblbase
		add ecx,4
		push eax
		mov eax,0x590890
		call eax

		lea ecx,&arg2
		lea edx,&arg3
		mov eax,tblbase
		add eax,0x14
		push ecx
		push edx
		mov ecx,eax
		mov eax,0x61CCD0
		call eax

		mov eax,tblbase
		mov [eax],0x6A984C
		mov [0x8186F4],eax
	}

	HANDLE	hFile = CreateFile("injectlist\\item_org_us.tbl", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	dwSizeLow = GetFileSize(hFile, &dwSizeHigh);
	BYTE* pDatas = new BYTE[dwSizeLow];
	ReadFile(hFile,pDatas,dwSizeLow,&dwReaded,0);
	CloseHandle(hFile);

	asm
	{
		mov eax,&pDatas
		mov ecx,dwSizeLow
		push 0x1608
		push 0x6081
		push 0x831
		push ecx
		push eax
		mov eax,0x44F670
		call eax
		add esp,0x14
	}

	hFile = CreateFile("injectlist\\item_org_us.tbl.tmp",GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile,pDatas,dwSizeLow,&dwReaded,NULL);
	CloseHandle(hFile);
	delete [] pDatas; pDatas = NULL;

	hFile = CreateFile("injectlist\\item_org_us.tbl.tmp",GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	asm
	{
		mov ecx,tblbase
		mov eax,hFile
		push eax
		mov eax,0x6270D0
		call eax
	}

	CloseHandle(hFile);
	DeleteFile("injectlist\\item_org_us.tbl.tmp");
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	HMODULE hm;
	GetModuleHandleExA(0, "kojd_tbl.dll", &hm);
	FreeLibraryAndExitThread(hm,1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int i = ListBox1->ItemIndex;

	if( i == -1)
		return;

	switch(i)
	{
		case 0:
		if( !FileExists("injectlist\\Skill_Magic_Main_us.tbl") )
		{
			MessageBox(this->Handle, "TBL bulunamadi!","Hata", MB_ICONEXCLAMATION);
			return;
        }
		inject_skillmain();
		break;

		case 1:
		if( !FileExists("injectlist\\item_org_us.tbl") )
		{
			MessageBox(this->Handle, "TBL bulunamadi!","Hata", MB_ICONEXCLAMATION);
			return;
		}
		inject_itemorg();
		break;

		case 2:
		if( !FileExists("injectlist\\skill_magic_4.tbl") )
		{
			MessageBox(this->Handle, "TBL bulunamadi!","Hata", MB_ICONEXCLAMATION);
			return;
		}
		inject_skill4();
		break;
	}

	MessageBoxA(this->Handle, "TBL inject edildi.","Inject", MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if( !FileExists("injectlist\\Skill_Magic_Main_us.tbl")	||
		!FileExists("injectlist\\item_org_us.tbl") 			||
		!FileExists("injectlist\\skill_magic_4.tbl") 		)
	{
		MessageBox(this->Handle, "TBL'lariniz eksik olabilir. Inject basarisiz.","Hata", MB_ICONEXCLAMATION);
		return;
	}

	inject_skillmain();
	inject_itemorg();
	inject_skill4();

	MessageBoxA(this->Handle, "TBL inject edildi.","Inject", MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

