#include "pch.h"
#include "Address.h"
#include "Offset.h"

#define baseModule addr->baseModule
#define playerBase addr->playerBase
#define playerPed addr->playerPed


void Address::calcAddresses()
{
	cPAddr->godMode =	(uintptr_t*)mem::FindDMAAddy(playerPed, cPOffset->godMode);
	cPAddr->health =	(uintptr_t*)mem::FindDMAAddy(playerPed, cPOffset->health);
	cPAddr->recoil =	(uintptr_t)baseModule + cPOffset->recoil[0];
	cPAddr->rapidFire = (uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->rapidFire);
	cPAddr->ammo1 =		(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->ammo1);
	cPAddr->mag1 =		(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->mag1);
	cPAddr->ammo2 =		(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->ammo2);
	cPAddr->mag2 =		(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->mag2);
	cPAddr->grenades =	(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->grenades);	
}

Address* addr = new Address();
Address::Player* cPAddr = new Address::Player();
