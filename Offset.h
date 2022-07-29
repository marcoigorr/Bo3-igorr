#pragma once

class Offset
{
public:
	class Player
	{
	public:
		// "blackops3.exe" + 0A54BDE8
		std::vector<unsigned int> godMode =			{ 0x2A8 };
		std::vector<unsigned int> health =			{ 0x2C8 };			
		// "blackops3.exe"
		std::vector<unsigned int> recoil =			{ 0x26D36E0 };
		// "blackops3.exe" + 0A54BDE0
		std::vector<unsigned int> rapidFire =		{ 0x54 };
		std::vector<unsigned int> rapidFire2 =		{ 0xE80 };

		std::vector<unsigned int> clipAmmo =		{ 0x684 };
		std::vector<unsigned int> stockAmmo =		{ 0x648 };
		std::vector<unsigned int> ammo1 =			{ 0x688 };
		std::vector<unsigned int> mag1 =			{ 0x64C };
		std::vector<unsigned int> ammo2 =			{ 0x690 };
		std::vector<unsigned int> mag2 =			{ 0x654 };
		std::vector<unsigned int> ammo3 =			{ 0x698 };
		std::vector<unsigned int> mag3 =			{ 0x65C };
		std::vector<unsigned int> ammo4 =			{ 0x6A4 };
		std::vector<unsigned int> mag4 =			{ 0x668 };
		std::vector<unsigned int> specGun =			{ 0x6A0 };
		std::vector<unsigned int> grenades =		{ 0x68C };
		std::vector<unsigned int> grenadesSpec =	{ 0x69C };
		
		std::vector<unsigned int> movementSpeed =	{ 0x5C70 };
		std::vector<unsigned int> points =			{ 0x16E84 };
	};

	class Zombie
	{
	public:
		// "blackops3.exe" + 0A5701B8
		std::vector<unsigned int> pos =			{ 0x1C };
		std::vector<unsigned int> health =		{ 0x2C8 };
	};
	
};

extern Offset* offset;
extern Offset::Player* cPOffset;
extern Offset::Zombie* cZOffset;
