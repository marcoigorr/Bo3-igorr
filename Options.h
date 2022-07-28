#pragma once

class Options
{
public:
	bool isEjecting = false;

	// cheat features
	bool bMenu = true;
	bool bGodMode = false, bInfHealth = false, bNoRecoil = false;

	bool* features[3] = {
		&bGodMode, &bInfHealth, &bNoRecoil
	};

	static void SetAllFalse();
	static void SetAllTrue();
};

extern Options* options;
