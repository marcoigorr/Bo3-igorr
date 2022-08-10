#pragma once

class Address
{
public:
	uintptr_t baseModule = (uintptr_t)GetModuleHandle(L"blackops3.exe");
	uintptr_t playerBase = baseModule + 0x0A54BDE0;
	uintptr_t playerPed = baseModule + 0x0A54BDE8;
	uintptr_t zombieCount = baseModule + 0x0A54BE40;
	uintptr_t zombieBase = baseModule + 0x0A5701B8;

	uintptr_t round = baseModule + 0xA55DDEC;

	void calcAddresses();

	class Player
	{
	public:
		uintptr_t* godMode;
		uintptr_t* health;
		uintptr_t recoil;
		uintptr_t* rapidFire;
		uintptr_t* rapidFire2;
		uintptr_t* clipAmmo;
		uintptr_t* stockAmmo;
		uintptr_t* ammo1;
		uintptr_t* ammo2;
		uintptr_t* ammo3;
		uintptr_t* ammo4;
		uintptr_t* mag1;		
		uintptr_t* mag2;
		uintptr_t* mag3;
		uintptr_t* mag4;
		uintptr_t* specGun;
		uintptr_t* grenades;
		uintptr_t* grenadesSpec;
		uintptr_t* movementSpeed;
		uintptr_t* points;
	};

	class Zombie
	{
	public:
		uintptr_t* count;
	};

};

extern Address* addr;
extern Address::Player* cPAddr;
extern Address::Zombie* cZAddr;

