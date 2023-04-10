#pragma once

#include <Windows.h>
#include <list>

class ManualControl
{
public:
	enum{KEY_A = 0x41, KEY_W = 0x57};
	ManualControl();
	bool isKeyPressed(short key);
	std::list<short>& getPressedKeys();
	int getDisplaySizeX();
	int getDisplaySizeY();
	int getDisplayMiddleX();
	int getDisplayMiddleY();
	int getMouseX();
	int getMouseY();
private:
	std::list<short> pressedKeys;
	int screenWidth;
	int screenHeight;
	int middleW;
	int middleH;
	
};

