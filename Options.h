#pragma once

class Options
{
public:
	bool isEjecting = false;

	// cheat features
	bool bMenu = true;
	bool bGodMode = false, bInfHealth = false, bNoRecoil = false, bInfiniteAmmo = false, bRapidFire = false;

	bool* features[5] = {
		&bGodMode, &bInfHealth, &bNoRecoil, &bInfiniteAmmo, &bRapidFire
	};

	static void SetAllFalse();
	static void SetAllTrue();
};

extern Options* options;
