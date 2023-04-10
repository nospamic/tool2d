#include "city.h"

City::City() : scene(Array3d<char>(Size3d(), ' ')), brush("@$8W9H4Z1l(r/!:.")
{
}

City::City(Size3d size) : size(size), scene(Array3d<char>(size, ' ')), brush("@@$8W9H4Z1l(r/!:..")
{
	brushSize = 19;
	step = 100;
	Tool3d::setBall(scene, Area3d(Point3d(size.x / 2, size.y / 2, 30), Size3d(50, 50, 30)), '.');
	Tool3d::setCuboid(scene, Area3d(Point3d(0, 0, size.z - 7), Size3d(size.x, size.y, 7)), '.', '.');
	for (int y = 0; y < size.y; y+=step) {
		for (int x = 0; x < size.x; x+=step) {
			int roulet = rand() % 50;
			int color = 1 + rand() % 15;
			Tool3d::setLine(scene, Point3d(x, 0, size.z - 1), Point3d(x, size.y - 1, size.z - 1), '.');
			Tool3d::setLine(scene, Point3d(0, y, size.z - 1), Point3d(size.x - 1, y, size.z - 1), '.');
			scene.set(Point3d(x, y, 0), '#');

			if (roulet < 10) {
				addSimpleBox(color, Point(x, y));
			}
			if (roulet > 10 && roulet < 28) {
				addZebra(color, Point(x, y));
			}
			if (roulet > 28 && roulet < 33) {
				addLayers(color, Point(x, y));
			}
			if (roulet > 33 && roulet < 50) {
				addWindows(color, Point(x, y));
			}
		}
	}
	setLight();
}

Array3d<char>& City::getCity()
{
	return scene;
}

void City::addSimpleBox(int color, Point point)
{
	int xSize = 50 + rand() % 30;
	int ySize = 50 + rand() % 30;
	int zSize = 10 + rand() % 20;
	Point3d position(point.x + (step - xSize) / 2, point.y + (step - ySize) / 2, size.z - zSize);
	Area3d area(position, Size3d(xSize, ySize, zSize));
	Tool3d::setCuboid(scene, area, brush[color], '.');
}

void City::addZebra(int color, Point point)
{
	int xSize = 50 + rand() % 30;
	int ySize = 50 + rand() % 30;
	int zSize = 50 + rand() % 100;
	Point3d position(point.x + (step - xSize) / 2 + 2, point.y + (step - ySize) / 2 + 2, size.z - zSize);
	Area3d area(position, Size3d(xSize - 4, ySize - 4, zSize));
	Tool3d::setCuboid(scene, area, brush[18 - color], '.');
	for (int z = 0; z < zSize; z+=8) {
		Point3d position(point.x + (step - xSize) / 2, point.y + (step - ySize) / 2, size.z - zSize + z);
		Area3d area(position, Size3d(xSize, ySize, 4));
		Tool3d::setCuboid(scene, area, brush[color], '.');
	}
	
}

void City::addLayers(int color, Point point)
{
	int xSize = 50 + rand() % 30;
	int ySize = 50 + rand() % 30;
	int zSize = 50 + rand() % 100;
	
	for (int z = 0; z < zSize; z += 8) {
		Point3d position(point.x + (step - xSize) / 2, point.y + (step - ySize) / 2, size.z - zSize + z);
		Area3d area(position, Size3d(xSize, ySize, 4));
		Tool3d::setCuboid(scene, area, brush[color], '.');
	}
}

void City::addWindows(int color, Point point)
{
	int windowSize = 4;
	int windowAdd = rand() % 3;
	int xSize = 50 + rand() % 30;
	int ySize = 50 + rand() % 30;
	int zSize = 20 + rand() % 70;
	Point3d position(point.x + (step - xSize) / 2, point.y + (step - ySize) / 2, size.z - zSize);
	Area3d area(position, Size3d(xSize, ySize, zSize));
	Tool3d::setCuboid(scene, area, brush[color], '.');
	for (int z = 1; z < zSize; z += windowSize * 2) {
		for (int y = 0; y < ySize; y += windowSize * 2) {
			for (int x = 0; x < xSize; x += windowSize * 2) {
				if (1) {
					Tool3d::setCuboid(scene, 
									Area3d(Point3d(x + position.x, y + position.y, z + position.z), 
									Size3d(windowSize + windowAdd, windowSize + windowAdd, windowSize + windowAdd)), 
									brush[18 - color], '1');
				}
			}
		}
	}
}

void City::setLight()
{
	for (int z = 0; z < scene.getSize().z; ++z) {
		if (scene.getArray2d(z).isEmpty())
			continue;
		for (int y = 0; y < scene.getSize().y; ++y) {
			for (int x = 0; x < scene.getSize().x; ++x) {
				char item = scene.get(Point3d(x, y, z));
				if (item != scene.getBackground()) {
					short brushNumber = getBrushNumber(item);
					brushNumber = inRange(brushNumber - 3, brushSize);
					scene.set(Point3d(x, y, z), brush[brushNumber]);
					break;
				}
			}
		}
	}
}

short City::getBrushNumber(char sign)
{
	for (short i = 0; i < brushSize; ++i) {
		if (sign == brush[i])
			return i;
	}
	return 0;
}
