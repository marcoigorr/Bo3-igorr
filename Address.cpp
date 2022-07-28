#include "pch.h"
#include "Address.h"
#include "Offset.h"

#define baseModule addr->baseModule
#define playerBase addr->playerBase
#define playerPed addr->playerPed


void Address::calcAddresses()
{
	cPAddr->godMode = (uintptr_t*)mem::FindDMAAddy(playerPed, cPOffset->godMode);
	cPAddr->health = (uintptr_t*)mem::FindDMAAddy(playerPed, cPOffset->health);
	cPAddr->recoil = (uintptr_t)baseModule + cPOffset->recoil[0];
}

Address* addr = new Address();
Address::Player* cPAddr = new Address::Player();
