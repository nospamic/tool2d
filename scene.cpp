#include "scene.h"

Screen::Screen()
{
    sizeX = 100;
    sizeY = 40;

    console = FastConsole (Size(sizeX, sizeY));;

}

void Screen::setMap(Map &map, int posX, int posY)
{
    Tool2d<char>pic(Size(sizeX, sizeY));
    pic.fill(' ');
    for(int y=0; y<sizeY; y++)
    {
        for(int x=0; x<sizeX; x++)
        {
            if(x+posX < map.sizeX && y+posY < map.sizeY) pic.set(x,y,map.space.get(x+posX,y+posY).symbol);
        }
    }
    console.setPicture(pic, Point(0, 0));

}

void Screen::setObject(Tool2d<Cell> &arr)
{
    Tool2d<char>pic(Size(arr.getSize().x, arr.getSize().y));
    pic.fill(' ');
    for(int y=0; y<arr.getSize().y; y++)
    {
        for(int x=0; x<arr.getSize().x; x++)
        {
            int type = arr.get(x,y).type;
            if(!(type==Cell::EMPTY
                 || type==Cell::SENSOR_F
                 || type==Cell::SENSOR_B))pic.set(x,y,arr.get(x,y).symbol);
        }
    }
    console.setPicture(pic, Point(sizeX/2 - pic.getSize().x/2, sizeY/2 - pic.getSize().y/2));

}

void Screen::setPicture(Tool2d<char> &arr,int x,int y)
{
    console.setPicture(arr,Point(x,y));
}

void Screen::show()
{
    console.show();
}

void Screen::text(int x, int y, std::string text)
{
    console.text(x,y,text);
}

void Screen::setMsg(std::string msg)
{
    console.setMsg(msg);
}
