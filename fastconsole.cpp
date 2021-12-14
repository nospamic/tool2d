#include "fastconsole.h"





FastConsole::FastConsole(Size size):size(size)
{
	scene = Scene(Area(Point(0, 0), size));
	screen = Array2d<char>(size, ' ');
	buffer = Array2d<char>(size, ' ');
	prepare();
	str.resize(size.x, ' ');
}

FastConsole::FastConsole()
{

}


void FastConsole::prepare()
{
    //setlocale (LC_ALL,"Russian");
    HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD maxWindow;
    maxWindow.X = size.x - 1;
    maxWindow.Y = size.y - 1;
    SMALL_RECT srctWindow = { 0, 0, maxWindow.X, maxWindow.Y};
    maxWindow.X = size.x;
    maxWindow.Y = size.y;
    SMALL_RECT minWindow = { 0, 0, 0, 0 };
    SetConsoleWindowInfo(out_handle, true, &minWindow);
    SetConsoleScreenBufferSize(out_handle, maxWindow);
    SetConsoleWindowInfo(out_handle, true, &srctWindow);
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    system("cls");
    std::ios_base::sync_with_stdio(0);
}

void FastConsole::setPicture(Array2d<char> &pic, Point position)
{
    for (int y = 0; y < pic.getSize().y; y++)
    {
        for (int x = 0; x < pic.getSize().x; x++)
        {
           if(x + position.x < size.x && y + position.y < size.y && pic.get(x,y) != ' ') 
			   buffer.set(Point(x+position.x, y+position.y), pic.get(x,y));
        }
    }
}

void FastConsole::setRectangle(Area area, char brush)
{
    Array2d<char> rec(area.size);
	Tool2d::setRectangle(rec, Area(Point(0, 0), area.size), brush, screen.getBackground());
    setPicture(rec, area.position);
}


void FastConsole::setCircle(Point topLeft, int radius, char brush)
{
    if (radius !=0){
        Array2d<char> circle(Size(radius*2+1,radius*2+1),' ');
        Tool2d::setCircle(circle, Point(0, 0), radius, brush);
        setPicture(circle, topLeft);
    }
}


void FastConsole::setLine(Area area, char brush){
    //Array2d<char>line(area.size, screen.getBackground());
    //Tool2d::setLine(line, Point(0,0), area.size, brush);
    //setPicture(line,area.position);
}


//void FastConsole::show()
//{

//    for (int y = 0; y < sizeY; y++)
//    {
//        std::string st = str;
//        for (int x = 0; x < sizeX; x++)
//        {
//            if (screen.get(x,y) != buffer.get(x,y))
//            {
//                screen.set(x, y, buffer.get(x,y));
//                if(!(x==sizeX-1 && y==sizeY-1))
//                {
//                    setCursor(x, y);
//                    std::flush(std::cout<<buffer.get(x,y));
//                }
//            }
//        }
//    }
//    setCursor(0,0);
//    reset();
//}


void FastConsole::show()
{
    for (int y = 0; y < size.y; y++)
    {
		if (!makeStr(y)) {
			continue;
		}
			
        setCursor(Point(0,y));
		if (y == size.y - 1) {
			str.pop_back();
			std::flush(std::cout << str);
			str.push_back(' ');
		}
		else {
			std::flush(std::cout << str);
		}
    }
    setCursor(Point(0,0));
    reset();
}

bool FastConsole::makeStr(int yPos)
{
	bool isChanged = false;
	for (int x = 0; x < size.x; x++)
	{
		char currentSymbol = buffer.get(x, yPos);
		if (currentSymbol != screen.get(x, yPos))
			isChanged = true;
		screen.set(x, yPos, currentSymbol);
		if (!(x == size.x - 1 && yPos == size.y - 1))
			str[x] = currentSymbol;
	}
	return isChanged;
}

void FastConsole::resetScr()
{
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            buffer.set(x, y, ' ');
            if (screen.get(x,y) != ' ')
            {
                screen.set(x, y, ' ');
                setCursor(Point(x, y));
                std::cout << ' ';
            }
        }
    }
}

void FastConsole::reset()
{
    buffer.fill(' ');
}

void FastConsole::text(Point position, std::string text)
{
    for(int n=position.x; n< position.x +text.size();n++){
        buffer.set(n,position.y, text[n - position.x]);
    }
}

void FastConsole::setMsg(std::string str){
	int x = (size.x - (unsigned(str.length())+4))/2;
    int y = (size.y - 5)/2;
    int w = str.length() + 4;
    int h = 5;
    Tool2d::setRectangle(buffer, Area(Point(x, y), Size( w, h)), '/', ' ');
    text(Point(x+2, y+2),str);
}

void FastConsole::setScene(Scene scene){
	this->scene = scene;
}


void FastConsole::setCursor(Point position)
{
        COORD coord;
        coord.X = position.x;
        coord.Y = position.y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


