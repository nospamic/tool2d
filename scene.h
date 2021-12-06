#ifndef SCREEN_H
#define SCREEN_H

#include <windows.h>

#include "fastconsole.h"
#include "Tool2d.h"


class Screen
{
public:
    Screen();

    int sizeX, sizeY;
    void setMap(Map &map, int posX, int posY);
    void setObject(Tool2d<Cell> &arr);
    void setPicture(Tool2d<char>&arr, int x, int y);
    void show();
    void text(int x, int y, std::string text);
    void setMsg(std::string msg);
private:
    FastConsole console;

};

#endif // SCREEN_H
