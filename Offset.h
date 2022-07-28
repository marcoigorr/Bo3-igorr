#pragma once

class Offset
{
public:
	class Player
	{
	public:
		// "blackops3.exe" + 0A54BDE8
		std::vector<unsigned int> godMode =		{ 0x2A8 };
		std::vector<unsigned int> health =		{ 0x2C8 };			
		// "blackops3.exe"
		std::vector<unsigned int> recoil =		{ 0x26D36E0 };
		// "blackops3.exe" + 0A54BDE0
		std::vector<unsigned int> rapidFire =	{ 0x54 };
		std::vector<unsigned int> ammo1 =		{ 0x688 };
		std::vector<unsigned int> mag1 =		{ 0x64C };
		std::vector<unsigned int> ammo2 =		{ 0x690 };
		std::vector<unsigned int> mag2 =		{ 0x654 };
		std::vector<unsigned int> grenades =	{ 0x68C };
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
