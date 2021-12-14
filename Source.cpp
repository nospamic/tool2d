#include <iostream>
#include"Tool2d.h"
#include "tool3d.h"

#include"fastconsole.h"

char gradient[] = ".:!/r(l1Z4H9W8$@";

void setCity(Array3d<char>& arr) {
	arr.getArray2d(28).fill(char(177));
	for (int i = 0; i < 40; ++i) {
		int x = 1 + rand() % 9;
		int y = 1 + rand() % 9;
		int z = rand() % 6;
		int grad = rand() % 15;
		Area3d area(Point3d(x * 15, y * 15, 28 - z), Size3d(10, 10, z));
		Tool3d::setCuboid(arr, area, gradient[grad], char(176));
	}
	for (int i = 0; i < 20; ++i) {
		int x = 4 + rand() % 6;
		int y = 4 + rand() % 6;
		int z = rand() % 17;
		int grad = rand() % 15;
		Area3d area(Point3d(x * 15, y * 15, 28 - z), Size3d(10, 10, z));
		Tool3d::setCuboid(arr, area, gradient[grad], char(176));
	}
}

void setEllipsoid(Array3d<char>& arr) {
	Tool3d::setBall(arr, Area3d(Point3d(50, 50, 10), Size3d(60, 60, 30)), '.');
	
	Tool3d::setBall(arr, Area3d(Point3d(20, 80, 17), Size3d(15, 15, 10)), '!');
	Tool3d::setLine(arr, Point3d(120, 80, 15), Point3d(125, 80, 15), 'Z');
	Tool3d::setLine(arr, Point3d(80, 136, 22), Point3d(80, 140, 22), '4');
	//Tool3d::setLightYZ(arr, 'r');

}


int main() {
	const int frameSize = 120;
	Array2d<char> frame[frameSize];

	FastConsole cons(Size(160, 40));
	Array3d<char> hold(Size3d(160, 160, 40), ' ');
	Array3d<char> pic(Size3d(160, 160, 40), ' ');

	//setEllipsoid(hold);
	setCity(hold);
	float fi = 0;
	for (int i = 0; i < frameSize; ++i) {
		pic = hold;
		Tool3d::rotateZ(pic, Point(80, 80), fi);
		//pic.set(Point3d(20,20,15), '@');
		//Tool3d::setLightYZ(pic, 'r');
		Array2d<char>plane = Tool3d::getPlaneXZ(pic);
		frame[i] = plane;// pic.getArray2d(20);
		fi += 3;
	}

	while (true) {
		int i = 0;
		for (; i < frameSize; ++i) {
			cons.setPicture(frame[i], Point(0, 0));
			cons.show();
			Sleep(50);
		}
		
	}
	std::cout << "\n";
	system("pause");
	return 0;
	
}