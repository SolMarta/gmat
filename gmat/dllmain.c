// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

BOOL APIENTRY DllMain (
		_In_	HMODULE	hModule,
		_In_	DWORD	ul_reason_for_call,
		_In_	LPVOID	lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		return _construct();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		return _destruct();
    }
    return TRUE;
}

