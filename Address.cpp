#include "pch.h"
#include "Address.h"
#include "Offset.h"

#define baseModule addr->baseModule
#define playerBase addr->playerBase
#define playerPed addr->playerPed
#define zombieCount addr->zombieCount


void Address::calcAddresses()
{
	cPAddr->godMode =		(uintptr_t*)mem::FindDMAAddy(playerPed, cPOffset->godMode);
	cPAddr->health =		(uintptr_t*)mem::FindDMAAddy(playerPed, cPOffset->health);
	cPAddr->recoil =		(uintptr_t)baseModule + cPOffset->recoil[0];
	cPAddr->rapidFire =		(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->rapidFire);
	cPAddr->rapidFire2 =	(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->rapidFire2);
	cPAddr->clipAmmo =		(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->clipAmmo);
	cPAddr->stockAmmo =		(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->stockAmmo);
	cPAddr->ammo1 =			(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->ammo1);
	cPAddr->ammo2 =			(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->ammo2);
	cPAddr->ammo3 =			(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->ammo3);
	cPAddr->ammo4 =			(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->ammo4);
	cPAddr->mag1 =			(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->mag1);
	cPAddr->mag2 =			(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->mag2);
	cPAddr->mag3 =			(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->mag3);
	cPAddr->mag4 =			(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->mag4);
	cPAddr->specGun =		(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->specGun);
	cPAddr->grenades =		(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->grenades);	
	cPAddr->grenadesSpec =	(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->grenadesSpec);	
	cPAddr->movementSpeed =	(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->movementSpeed);
	cPAddr->points =		(uintptr_t*)mem::FindDMAAddy(playerBase, cPOffset->points);

	cZAddr->count =			(uintptr_t*)mem::FindDMAAddy(zombieCount, cZOffset->count);
}

Address* addr = new Address();
Address::Player* cPAddr = new Address::Player();
Address::Zombie* cZAddr = new Address::Zombie();

