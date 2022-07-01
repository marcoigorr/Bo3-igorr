// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "mem.h"
#include "Offsets.hpp"

void Log(const std::string& text) {
    std::ofstream log("C:\\logs\\Bo3-igorr.log", std::ofstream::app | std::ofstream::out);
    log << "[+] " << std::hex << std::uppercase << text.c_str() << std::endl;
}

DWORD WINAPI MainThread(HMODULE hModule)
{
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"blackops3.exe");

    bool ejectDLL = false;
    bool bAmmo = false, bGAmmo = false;
    bool bHealth = false, bGHealth = false;
    bool bEntCout = false;

    while (!ejectDLL)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            ejectDLL = true;
            Log("Ejecting dll...");
        }     

        uintptr_t clientAttributes = moduleBase + 0x0A54BDE8; // hp
        uintptr_t clientWeapon = moduleBase + 0x0A54BDE0; // ammo/mag/grenades
        uintptr_t clientInfo = moduleBase + 0x179086D8; // nick/points

        // -- unlimited ammo (you)
        if (GetAsyncKeyState(VK_F1) & 1 || ejectDLL)
            bAmmo = !bAmmo;

        if (bAmmo && !ejectDLL)
        {
            uintptr_t* ptrAmmo1 = (uintptr_t*)mem::FindDMAAddy(clientWeapon, Offsets::p_ammo1);
            uintptr_t* ptrAmmo2 = (uintptr_t*)mem::FindDMAAddy(clientWeapon, Offsets::p_ammo2);

            if (ptrAmmo1)
                *(int*)ptrAmmo1 = 50;

            if (ptrAmmo2)
                *(int*)ptrAmmo2 = 50;
        }

        // -- god mode (you)
        if (GetAsyncKeyState(VK_F2) & 1 || ejectDLL) 
            bHealth = !bHealth;

        if (bHealth && !ejectDLL)
        {            
            uintptr_t* ptrHealth = (uintptr_t*)mem::FindDMAAddy(clientAttributes, Offsets::p_health);
            if (ptrHealth)
                *(int*)ptrHealth = 300;
        }

        // -- global god mode
        if (GetAsyncKeyState(VK_F3) & 1 || ejectDLL) 
        {
            bGHealth = !bGHealth;
            if (bGHealth && !ejectDLL) // nop -> blackops3.exe+18B9AC4 - 44 29 BE C8020000 - sub [rsi+000002C8],r15d (sub hp on hit)
            {
                mem::Nop((BYTE*)moduleBase + 0x18B9AC4, 7);
            }
            else // Patch
            {
                mem::Patch((BYTE*)moduleBase + 0x18B9AC4, (BYTE*)"\x44\x29\xBE\xC8\x02\x00\x00", 7);
            }
        }

        // -- global unlimited ammo
        if (GetAsyncKeyState(VK_F4) & 1 || ejectDLL) 
        {
            bGAmmo = !bGAmmo;

            if (bGAmmo && !ejectDLL) // nop -> blackops3.exe+26E71EA - 45 89 18 - mov [r8],r11d (ammo dec)
            {
                mem::Nop((BYTE*)moduleBase + 0x26E71EA, 3);
            }
            else // Patch
            {
                mem::Patch((BYTE*)moduleBase + 0x26E71EA, (BYTE*)"\x45\x89\x18", 3);
            }
        }

        // -- points
        if (GetAsyncKeyState(VK_F5) & 1 || ejectDLL)
        {
            uintptr_t* ptrPoints = (uintptr_t*)mem::FindDMAAddy(clientInfo, Offsets::p_points);
            if (ptrPoints)
                *(int*)ptrPoints += 500;
        }

        // -- max ammo
        if (GetAsyncKeyState(VK_F6) & 1 || ejectDLL)
        {
            uintptr_t* ptrMag1 = (uintptr_t*)mem::FindDMAAddy(clientWeapon, Offsets::p_mag1);
            uintptr_t* ptrMag2 = (uintptr_t*)mem::FindDMAAddy(clientWeapon, Offsets::p_mag2);
            uintptr_t* ptrGrenades = (uintptr_t*)mem::FindDMAAddy(clientWeapon, Offsets::p_grenades);

            if (ptrMag1)
                *(int*)ptrMag1 = 800;

            if (ptrMag2)
                *(int*)ptrMag2 = 800;

            if (ptrGrenades)
                *(int*)ptrGrenades = 6;
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
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

