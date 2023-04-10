#include <iostream>
#include"Tool2d.h"
#include "tool3d.h"
#include "camera.h"
#include"fastconsole.h"
#include "manualControl.h"
#include "city.h"






char gradient[] = ".:!/r(l1Z4H9W8$@";

Size consoleSize(280, 65);
int sceneX = 1000;
int sceneY = 1000;
int sceneZ = 300;
Size3d sceneSize(sceneX, sceneY, sceneZ);
Point center(sceneSize.x / 2, sceneSize.y / 2);
float xPosition = float(sceneSize.x / 2 - 50);
float xStep = 0.3f;
float camAngle = 0;
Point3d cameraPosition = Point3d(xPosition, 0, 0);


ManualControl control;



void setLightYZ(Array3d<char>& arr)
{
	
	char gradient[] = "@$8W9H4Z1l(r/!:.";
	int gradSize = 16;
	for (int z = 0; z < arr.getSize().z; ++z) {
		if (arr.getArray2d(z).isEmpty())
			continue;
		for (int y = 0; y < arr.getSize().y; ++y) {
			for (int x = 0; x < arr.getSize().x; ++x) {
				char light = gradient[int(float(gradSize) / float(arr.getSize().x) * float(x))];
				if (arr.get(Point3d(x, y, z)) != arr.getBackground()) {
					arr.set(Point3d(x, y, z), light);
					break;
				}
			}
		}
	}
}

void setCity(Array3d<char>& arr) {
	//arr.getArray2d(sceneZ - 2).fill(char(177));
	Tool3d::setBall(arr, Area3d(Point3d(center.x - 30, center.y - 30, 100), Size3d(60, 60, 28)), '.');
	for (int i = 0; i < 160; ++i) {
		int x = 1 + rand() % 50;
		int y = 1 + rand() % 50;
		int z = rand() % (sceneZ/10);
		int grad = rand() % 15;
		Area3d area(Point3d(x * 15, y * 15, sceneZ - z), Size3d(30, 30, z));
		Tool3d::setCuboid(arr, area, gradient[grad], char(176));
	}
	for (int i = 0; i < 100; ++i) {
		int x = 4 + rand() % 40;
		int y = 4 + rand() % 40;
		int z = rand() % (sceneZ/5);
		int grad = rand() % 15;
		Area3d area(Point3d(x * 15, y * 15, sceneZ - z), Size3d(30, 30, z));
		Tool3d::setCuboid(arr, area, gradient[grad], char(176));
	}
}

void setCar(Array3d<char>& car) {
	

}

void setEllipsoid(Array3d<char>& arr) {
	//Tool3d::setBall(arr, Area3d(Point3d(center.x - 30, center.y - 30, 10), Size3d(60, 60, 28)), '.');
	
	Tool3d::setBall(arr, Area3d(Point3d(55, 80, 17), Size3d(15, 15, 8)), ' ');

	Tool3d::setCuboid(arr, Area3d(Point3d(37, 50, 24), Size3d(25, 30, 1)), ':', ' ');
	Tool3d::setCuboid(arr, Area3d(Point3d(37, 50, 26), Size3d(25, 30, 1)), ':', ' ');
	Tool3d::setCuboid(arr, Area3d(Point3d(37, 50, 28), Size3d(25, 30, 1)), ':', ' ');
	Tool3d::setCuboid(arr, Area3d(Point3d(37, 50, 30), Size3d(25, 30, 1)), ':', ' ');

	Tool3d::setCuboid(arr, Area3d(Point3d(123, 123, 27), Size3d(40, 40, 3)), '.', '1');

	Tool3d::setBall(arr, Area3d(Point3d(137, 80, 17), Size3d(30, 30, 15)), '!');


	//Tool3d::setLine(arr, Point3d(0, 0, 0), Point3d(200, 200, 50), '.');
	//Tool3d::setLine(arr, Point3d(80, 136, 22), Point3d(80, 140, 22), '4');
	//Tool3d::setLightYZ(arr, 'r');

}


int main() {
	const int frameSize = 360;
	Array2d<char> frame[frameSize];

	FastConsole cons(consoleSize);
	//Array3d<char> hold(sceneSize, ' ');
	Array3d<char> pic(sceneSize, ' ');

	//setEllipsoid(hold);
	//setCity(hold);
	//setCar(hold);
	Camera<char> camera(Point3d(1000, 1000, 100), consoleSize);
	City city(Size3d(2000, 2000, 200));
	Array3d<char>hold = city.getCity();

	
	camera.capture(hold);
	cons.setPicture(camera.getScreen(), Point(0, 0));
	cons.show();
	int currentMouseX = control.getMouseX();
	int currentMouseY = control.getMouseY();
	bool hasChanges = false;
	while (true) {
		
		if (control.getMouseX() != currentMouseX || control.getMouseY() != currentMouseY) {
			currentMouseX = control.getMouseX();
			currentMouseY = control.getMouseY();
			camera.rotateHorizontal(-(float)currentMouseX / 3.0f);
			camera.rotateVertical(((float)currentMouseY - control.getDisplayMiddleY()) / 3.0f);
			hasChanges = true;
		}
		if (control.isKeyPressed(ManualControl::KEY_W)) {
			camera.moveForward(3);
			hasChanges = true;
		}
		if (hasChanges) {
			camera.capture(hold);
			cons.setPicture(camera.getScreen(), Point(0, 0));
			cons.setMsg(std::to_string(camera.getAngle()));
			cons.show();
			hasChanges = false;
		}
	}



	float fi = 0;
	//camAngle = -40;
	camera.rotateHorizontal(camAngle);
	for (int i = 0; i < frameSize; ++i) {
		pic = hold;
		Tool3d::rotateZ(pic, center, fi);
		//Tool3d::setLightYZ(pic, 'r');
		setLightYZ(pic);
		camera.capture(pic);
		Array2d<char>plane = camera.getScreen();// Tool3d::getPlaneXZ(pic);
		frame[i] = std::move(plane);// pic.getArray2d(20);
		fi += 1.0f;

		xPosition += xStep;
		camAngle += 0.2f;
		cameraPosition = Point3d(myRound(xPosition), 0, sceneSize.z / 2);
		//camera.mooveTo(cameraPosition);
		//camera.rotateZ(camAngle);
		
	}

	while (true) {
		int i = 0;
		for (; i < frameSize; ++i) {
			cons.setPicture(frame[i], Point(0, 0));
			cons.show();
			Sleep(13);
		}
		
	}
	std::cout << "\n";
	system("pause");
	return 0;
	
}