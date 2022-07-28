#pragma once

class Offset
{
public:
	class Player
	{
	public:
		std::vector<unsigned int> godMode =		{ 0x2A8 };
		std::vector<unsigned int> health =		{ 0x2C8 };		
		std::vector<unsigned int> recoil =		{ 0x26D36E0 };
	};
	
};

extern Offset* offset;
extern Offset::Player* cPOffset;
