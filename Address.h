#pragma once

class Address
{
public:
	uintptr_t baseModule = (uintptr_t)GetModuleHandle(L"blackops3.exe");
	uintptr_t playerBase = baseModule + 0x0A54BDE0;
	uintptr_t playerPed = baseModule + 0x0A54BDE8;

	void calcAddresses();

	class Player
	{
	public:
		uintptr_t* godMode;
		uintptr_t* health;
		uintptr_t recoil;
	};

};

extern Address* addr;
extern Address::Player* cPAddr;
