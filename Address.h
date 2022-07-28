#pragma once

class Address
{
public:
	uintptr_t baseModule = (uintptr_t)GetModuleHandle(L"blackops3.exe");
	uintptr_t playerBase = baseModule + 0x0A54BDE0;
	uintptr_t playerPed = baseModule + 0x0A54BDE8;
	uintptr_t zombieBase = baseModule + 0x0A5701B8;

	void calcAddresses();

	class Player
	{
	public:
		uintptr_t* godMode;
		uintptr_t* health;
		uintptr_t recoil;
		uintptr_t* rapidFire;
		uintptr_t* ammo1;
		uintptr_t* mag1;
		uintptr_t* ammo2;
		uintptr_t* mag2;
		uintptr_t* grenades;
	};

};

extern Address* addr;
extern Address::Player* cPAddr;
