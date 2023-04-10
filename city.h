#pragma once
#include "tool3d.h"


class City
{
public:
	enum{SIMPLE_BOX, ZEBRA, LAYERS,WINDOWS, PARKING, STADIUM, ANTENNA};
	City();
	City(Size3d size);
	Array3d<char>& getCity();
private:
	void addSimpleBox(int color, Point point);
	void addZebra(int color, Point point);
	void addLayers(int color, Point point);
	void addWindows(int color, Point point);
	void setLight();
	short getBrushNumber(char sign);
	Size3d size;
	Array3d<char> scene;
	const char brush[19];
	short brushSize;
	int step;

};

