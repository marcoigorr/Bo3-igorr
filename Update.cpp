#include "pch.h" 
#include "mem.h"
#include "Offsets.hpp"
#include "Update.h"
#include "Options.h"

#define ejectDLL Options::ejectDLL

void update::Log(const std::string& text) {
    std::ofstream log("C:\\logs\\Bo3-igorr.log", std::ofstream::app | std::ofstream::out);
    log << "[+] " << std::hex << std::uppercase << text.c_str() << std::endl;
}

void update::Hack(uintptr_t moduleBase)
{
    uintptr_t clientAttributes = moduleBase + 0x0A54BDE8; // hp
    uintptr_t clientWeapon = moduleBase + 0x0A54BDE0; // ammo/mag/grenades/rapidfire
    uintptr_t clientInfo = moduleBase + 0x179086D8; // nick/points
    uintptr_t zm_entList = moduleBase + 0x0A5701B8; //zm_hp/zm_pos

    // Getting zombie number based on R (round number)
    // Formula is not precise but it save some time when looping through ent list
    uintptr_t zm_roundAddr = (uintptr_t)moduleBase + 0xA55DDEC;
    int R = *(int*)zm_roundAddr;
    int zm_number = 0.000225f * pow(R, 3) + 0.314314f * pow(R, 2) + 1.835712f * R + 27.596132f;

    if (GetAsyncKeyState(VK_END) & 1) // debug
    {        
        Log(std::to_string(zm_number));
    }
    
    // -- loop through zm list
    int entCount = 0;
    for (long long i = 0; i < zm_number; i++)
    {
        uintptr_t* ptrEntityHealth = (uintptr_t*)mem::FindDMAAddy(zm_entList + (i * 0x2110), Offsets::zm_health);
        if (ptrEntityHealth)
        {
            if (*(int*)ptrEntityHealth <= 0) continue;
            // -- Ent count
            entCount++;

            // -- Instant Kill
            if (Options::bInstantKill)
                *(int*)ptrEntityHealth = 1; // set zm_hp to 1
        }
    }

    // -- unlimited ammo (you)
    if (GetAsyncKeyState(VK_F1) & 1)
        Options::bAmmo = !Options::bAmmo;

    if (Options::bAmmo && !ejectDLL) // freeze
    {
        uintptr_t* ptrAmmo1 = (uintptr_t*)mem::FindDMAAddy(clientWeapon, Offsets::p_ammo1);
        uintptr_t* ptrAmmo2 = (uintptr_t*)mem::FindDMAAddy(clientWeapon, Offsets::p_ammo2);
        uintptr_t* ptrGrenades = (uintptr_t*)mem::FindDMAAddy(clientWeapon, Offsets::p_grenades);

        if (ptrAmmo1)
            *(int*)ptrAmmo1 = 50;

        if (ptrAmmo2)
            *(int*)ptrAmmo2 = 50;

        if (ptrGrenades)
            *(int*)ptrGrenades = 6;
    }

    // -- global unlimited ammo
    if (GetAsyncKeyState(VK_F2) & 1 || ejectDLL)
    {
        Options::bGAmmo = !Options::bGAmmo;

        if (Options::bGAmmo && !ejectDLL) // nop -> blackops3.exe+26E71EA - 45 89 18 - mov [r8],r11d (ammo dec)
        {
            mem::Nop((BYTE*)moduleBase + 0x26E71EA, 3);
        }
        else // Patch
        {
            mem::Patch((BYTE*)moduleBase + 0x26E71EA, (BYTE*)"\x45\x89\x18", 3);
        }
    }

    // -- god mode (you)
    if (GetAsyncKeyState(VK_F3) & 1)
        Options::bHealth = !Options::bHealth;

    if (Options::bHealth && !ejectDLL) // freeze
    {
        uintptr_t* ptrHealth = (uintptr_t*)mem::FindDMAAddy(clientAttributes, Offsets::p_health);
        if (ptrHealth)
            *(int*)ptrHealth = 300;
    }

    // -- global god mode
    if (GetAsyncKeyState(VK_F4) & 1 || ejectDLL)
    {
        Options::bGHealth = !Options::bGHealth;
        if (Options::bGHealth && !ejectDLL) // nop -> blackops3.exe+18B9AC4 - 44 29 BE C8020000 - sub [rsi+000002C8],r15d (sub hp on hit)
        {
            mem::Nop((BYTE*)moduleBase + 0x18B9AC4, 7);
        }
        else // Patch
        {
            mem::Patch((BYTE*)moduleBase + 0x18B9AC4, (BYTE*)"\x44\x29\xBE\xC8\x02\x00\x00", 7);
        }
    }   

    // -- points
    if (GetAsyncKeyState(VK_F5) & 1)
    {
        uintptr_t* ptrPoints = (uintptr_t*)mem::FindDMAAddy(clientInfo, Offsets::p_points);
        if (ptrPoints)
            *(int*)ptrPoints += 500;
    }

    // -- max ammo
    if (GetAsyncKeyState(VK_F6) & 1)
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

    // -- Zombie count
    if (GetAsyncKeyState(VK_F7) & 1)
    {
        // Options::bEntCout = !Options::bEntCout;
        Log("Ent count = " + std::to_string(entCount));
    }               

    // -- instant kill
    if (GetAsyncKeyState(VK_F8) & 1)
        Options::bInstantKill = !Options::bInstantKill;

    // -- Rapid fire (you) don't buy soda or gubblegum while this is active.
    if (GetAsyncKeyState(VK_F9) & 1)
        Options::bRapidFire = !Options::bRapidFire;

    if (Options::bRapidFire && !ejectDLL)
    {
        uintptr_t* ptrRapidFire = (uintptr_t*)mem::FindDMAAddy(clientWeapon, Offsets::p_rapidFire);
        if (ptrRapidFire)
            *(short int*)ptrRapidFire = 0;
    }

    // -- global Rapid fire
    if (GetAsyncKeyState(VK_F10) & 1 || ejectDLL)
    {
        Options::bGRapidFire = !Options::bGRapidFire;

        if (Options::bGRapidFire && !ejectDLL) // nop -> blackops3.exe+26E50B8 - 41 89 00 - mov[r8],eax
        {                                     // nop -> blackops3.exe+26E50D7 - 41 89 08 - mov[r8],ecx
            mem::Nop((BYTE*)moduleBase + 0x26E50B8, 3);
            mem::Nop((BYTE*)moduleBase + 0x26E50D7, 3);
        }
        else // Patch
        {
            mem::Patch((BYTE*)moduleBase + 0x26E50B8, (BYTE*)"\x41\x89\x00", 3);
            mem::Patch((BYTE*)moduleBase + 0x26E50D7, (BYTE*)"\x41\x89\x08", 3);
        }
    }

    // -- Freeze Current divinum
    if (GetAsyncKeyState(VK_F11) & 1 || ejectDLL)
    {
        Options::bDivinumFreeze = !Options::bDivinumFreeze;

        if (Options::bDivinumFreeze && !ejectDLL) // nop -> blackops3.exe+1E0AC88 - 89 6C 18 24 - mov [rax+rbx+24],ebp
        {
            mem::Nop((BYTE*)moduleBase + 0x1E0AC88, 4);
        }
        else // Patch
        {
            mem::Patch((BYTE*)moduleBase + 0x1E0AC88, (BYTE*)"\x89\x6C\x18\x24", 4);
        }
    }    
}
