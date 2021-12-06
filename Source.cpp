#include<iostream>
#include"Tool2d.h"
#include "tool3d.h"

#include"fastconsole.h"


Array2d<int> get() {
	Array2d<int> arr(Size(100000, 1500));
	arr.fill(200);
	return arr;
}

void show(const Tool2d<char> &arr) {
	for (int y = 0; y < arr.getSize().y; ++y) {
		for (int x = 0; x < arr.getSize().x; ++x)
			std::cout << arr.get(x, y) << " ";
		std::cout << "\n";
	}
}

int main() {

	Tool3d<char> t3d(Size3d(200, 200, 20));
	t3d.fill('+');
	FastConsole cons(Size(80, 20));
	for (float f = 0; f < 580; f+=1.5f) {
		Tool2d<char>pic(Size(200,200), ' ');
		Tool2d<char>pic2(Size(200, 200), ' ');
		pic.setRectangle(Point(5, 5), Size(90, 25), 'O', '.');
		pic2.setRectangle(Point(20, 10), Size(40, 90), 'O', '+');
		pic.setCircle(Point(10, 10), 40, '#');
		
		pic2.setCircle(Point(20, 15), 10, '0');
		pic.rotate(Point(25, 15), f);
		pic2.rotate(Point(40, 25), -f*3);
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