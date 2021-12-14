#ifndef FASTCONSOLE_H
#define FASTCONSOLE_H

#include <iostream>
#include <windows.h>
#include <string>
#include "Tool2d.h"

class Scene{
public:
	Scene() {};
	Scene(Area area) :area(area) {
	}
	Area area;
};

class FastConsole
{
public:
    FastConsole(Size size);
    FastConsole();

    void prepare();
	Size size;
    void setPicture (Array2d<char>&pic, Point position);
    void setRectangle(Area area, char brush);
    void setCircle(Point center, int radius, char brush);
    void setLine(Area area, char brush);
    void show();
    void resetScr();
    void reset();
    void text(Point position, std::string text);
    void setMsg(std::string str);
	void setScene(Scene scene);


private:
    Array2d<char> screen;
    Array2d<char> buffer;
    void setCursor(Point position);
    std::string str;
	bool makeStr(int yPos);
	Scene scene;
};

#endif // FASTCONSOLE_H