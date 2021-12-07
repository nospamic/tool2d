#include<iostream>
#include"Tool2d.h"
#include "array3d.h"

#include"fastconsole.h"




int main() {

	Array3d<char> t3d(Size3d(200, 200, 20));
	t3d = Array3d<char>(Size3d(200, 200, 20));
	t3d.fill('+');
	Array3d<char> t3d2(std::move(t3d));
	std::cout << t3d2.get(Point3d(2, 2, 10));

	FastConsole cons(Size(80, 20));
	for (float f = 0; f < 580; f+=1.5f) {
		Array2d<char>pic(Size(200,200), ' ');
		Array2d<char>pic2(Size(200, 200), ' ');
		Tool2d::setRectangle(pic, Area(Point(5, 5), Size(90, 25)), 'O', '.');
		Tool2d::setRectangle(pic2, Area(Point(20, 10), Size(40, 90)), 'O', '+');
		Tool2d::setCircle(pic, Point(10, 10), 40, '#');
		
		Tool2d::setCircle(pic2, Point(20, 15), 10, '0');
		Tool2d::rotate(pic, Point(25, 15), f);
		Tool2d::rotate(pic2, Point(40, 25), -f*3);
		cons.setPicture(pic, Point(0, 0));
		cons.setPicture(pic2, Point(0, 0));
		cons.setMsg("Hello rotation");
		//cons.setLine(Area(Point(10, 10), Size(1, 5)), '#');
		cons.show();
	}
	std::cout << "\n";
	system("pause");
	return 0;
	
}