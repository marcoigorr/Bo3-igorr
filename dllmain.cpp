// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "mem.h"

DWORD WINAPI MainThread(HMODULE hModule)
{
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"blackops3.exe");

    bool ejectDLL = false;
    bool bAmmo = false, bHealth = false;

    while (!ejectDLL)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            ejectDLL = true;
        }

        // uintptr_t* zm_entList = (uintptr_t*)moduleBase + 0x0A5701B8; // 7FF7277C01B8

        if (GetAsyncKeyState(VK_F1) & 1 || ejectDLL)
        {
            bAmmo = !bAmmo;

            if (bAmmo && !ejectDLL) // nop -> blackops3.exe+26E71EA - 45 89 18 - mov [r8],r11d (ammo dec)
            {
                mem::Nop((BYTE*)moduleBase + 0x26E71EA, 3);
            }
            else // Patch
            {
                mem::Patch((BYTE*)moduleBase + 0x26E71EA, (BYTE*)"\x45\x89\x18", 3);
            }
        }

        if (GetAsyncKeyState(VK_F2) & 1 || ejectDLL)
        {
            bHealth = !bHealth;

            if (bHealth && !ejectDLL) // nop -> blackops3.exe+18B9AC4 - 44 29 BE C8020000 - sub [rsi+000002C8],r15d (sub hp on hit)
            {
                mem::Nop((BYTE*)moduleBase + 0x18B9AC4, 7);
            }
            else // Patch
            {
                mem::Patch((BYTE*)moduleBase + 0x18B9AC4, (BYTE*)"\x44\x29\xBE\xC8\x02\x00\x00", 7);
            }
        }
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
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, NULL, NULL, NULL);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

