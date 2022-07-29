// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "mem.h"

#include "Address.h"
#include "Offset.h"

#include "Options.h"

#include "DX11.h"
using namespace d3d11Menu;

#define isEjecting options->isEjecting


DWORD WINAPI MainThread(HMODULE hModule)
{
    // Hook d3d11, render ImGUI
    if (!InitMenu())
    {
        isEjecting = true;
    }

    // Hack loop
    while (!isEjecting)
    {
        // Press END to eject dll
        isEjecting = ((GetAsyncKeyState(VK_END)) ? true : false);

        if (isEjecting)
        {
            options->SetAllFalse();
        }
        else
        {
            addr->calcAddresses();
        }

        // -- GodMode
        if (cPAddr->godMode)
        {
            if (options->bGodMode)
            {
                *(byte*)cPAddr->godMode = 9;
            }
            else
            {
                *(byte*)cPAddr->godMode = 8;
            }
        }

        // -- InfHealth
        if (cPAddr->health)
        {
            if (options->bInfHealth)
            {
                *(int*)cPAddr->health = 300;
            }
        }

        // -- NoRecoil
        if (cPAddr->recoil)
        {
            if (options->bNoRecoil)
            {
                *(int*)cPAddr->recoil = 195;
            }
            else
            {
                *(int*)cPAddr->recoil = 1220840264;
            }
        }

        // -- Ammo
        if (cPAddr->ammo1) // enough
        {
            if (options->bInfiniteAmmo)
            {
                *(int*)cPAddr->ammo1 = 99;
                *(int*)cPAddr->ammo2 = 99;
                *(int*)cPAddr->ammo3 = 99;
                *(int*)cPAddr->ammo4 = 99;
                *(int*)cPAddr->mag1 = 850;
                *(int*)cPAddr->mag2 = 850;
                *(int*)cPAddr->mag3 = 850;
                *(int*)cPAddr->mag4 = 850;
                *(int*)cPAddr->specGun = 420;
                *(int*)cPAddr->grenades = 10;
                *(int*)cPAddr->grenadesSpec = 10;
            }
        }

        // -- rapidFire
        if (cPAddr->rapidFire && cPAddr->rapidFire2)
        {
            if (options->bRapidFire)
            {
                *(int*)cPAddr->rapidFire = 0;
                *(int*)cPAddr->rapidFire2 = 0;
            }
        }

        // -- Points
        if (cPAddr->points)
        {
            if (options->bAddPoints)
            {
                *(int*)cPAddr->points += 500;
                options->bAddPoints = false;
            }
        }

        // -- Menu
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            options->bMenu = !options->bMenu;
        }
    }

    // Cleanup/Eject    
    if (!StopMenu()) {
        return 1;
    }
    FreeLibraryAndExitThread(hModule, 0);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
