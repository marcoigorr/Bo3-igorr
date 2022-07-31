#pragma once

class Options
{
public:
	bool isEjecting = false;

	// cheat features
	bool bMenu = true;
	bool bGodMode = false, bInfHealth = false, bNoRecoil = false, bInfiniteAmmo = false, bRapidFire = false, bSpeedHack = false, bDoublePoints = false;
	bool bAddPoints = false, bInstantKill = false;

	bool* features[7] = {
		&bGodMode, &bInfHealth, &bNoRecoil, &bInfiniteAmmo, &bRapidFire, &bSpeedHack, &bDoublePoints
	};

	static void SetAllFalse();
	static void SetAllTrue();
};

extern Options* options;
