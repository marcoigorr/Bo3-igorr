// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Update.h"
#include "Options.h"
using namespace Options;


DWORD WINAPI MainThread(HMODULE hModule)
{
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"blackops3.exe");    

    while (!ejectDLL)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            ejectDLL = true;
            update::Log("Ejecting dll...");
        }     

        update::Hack(moduleBase);        
    }

    FreeLibraryAndExitThread(hModule, 0);
    return 0;    
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

