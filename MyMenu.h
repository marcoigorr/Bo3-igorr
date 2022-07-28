#pragma once

class MyMenu
{
public:
	float WIDTH = 500;
	float HEIGHT = 700;

	static void SetStyle();
	static void Draw();
};

extern MyMenu* Menu;


