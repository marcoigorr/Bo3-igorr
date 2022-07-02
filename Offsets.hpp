#pragma once
#include "pch.h"

namespace Offsets
{
	// "blackops3.exe" + 0A5701B8
	std::vector<unsigned int> zm_pos = { 0x1C };
	std::vector<unsigned int> zm_health = { 0x2C8 };

	// "blackops3.exe" + 0A54BDE8
	std::vector<unsigned int> p_health = { 0x2C8 };

	// "blackops3.exe" + 0A54BDE0
	std::vector<unsigned int> p_rapidFire = { 0x54 };
	std::vector<unsigned int> p_ammo1 = { 0x688 };
	std::vector<unsigned int> p_mag1 = { 0x64C };
	std::vector<unsigned int> p_ammo2 = { 0x690 };
	std::vector<unsigned int> p_mag2 = { 0x654 };
	std::vector<unsigned int> p_grenades = { 0x68C };

	// "blackops3.exe"+179086D8
	std::vector<unsigned int> p_nickname= { 0x2C };
	std::vector<unsigned int> p_points = { 0x28C };
}
