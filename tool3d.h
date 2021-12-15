#pragma once
#include "array3d.h"
#include "Tool2d.h"

namespace Tool3d 
{
	template <typename T>
	void rotateZ(Array3d<T> &arr, Point center, float fi);

	template <typename T>
	Array2d<T> getPlaneXY(Array3d<T> &arr);

	template <typename T>
	Array2d<T> getPlaneXZ(Array3d<T> &arr);

	template <typename T>
	void setLightYZ(Array3d<T> &arr, T light);

	template <typename T>
	void setCuboid(Array3d<T> &arr, Area3d area, T brush, T fill);

	template <typename T>
	void setCylinder(Array3d<T> &arr, Area3d area, T brush);

	template <typename T>
	void setBall(Array3d<T> &arr, Area3d area, T brush);

	template <typename T>
	void setLine(Array3d<T> &arr, Point3d start, Point3d end, T brush);

	template <typename T>
	void setPoint(Array3d<T> &arr, Point3d start, T brush);
}

template <typename T>
inline void Tool3d::rotateZ(Array3d<T> &arr,Point center, float fi) {
	for (int z = 0; z < arr.getSize().z; ++z) {
		if (!arr.getArray2d(z).isEmpty())
			Tool2d::rotate(arr.getArray2d(z), center, fi);
	}
}

template <typename T>
inline Array2d<T> Tool3d::getPlaneXY(Array3d<T> &arr) {

}

template<typename T>
inline Array2d<T> Tool3d::getPlaneXZ(Array3d<T>& arr){
	Array2d<T> plane(Size(arr.getSize().x, arr.getSize().z), arr.getBackground());
	Point3d start = Point3d(arr.getSize().x / 2, 0, arr.getSize().z / 2);
	for (int z = 0; z < arr.getSize().z; ++z) {
		for (int x = 0; x < arr.getSize().x; ++x) {
			int lengthX = x - start.x;
			int lengthY = arr.getSize().y - 1;
			int lengthZ = z - start.z;

			float length = sqrt(lengthX*lengthX + lengthY*lengthY + lengthZ*lengthZ);
			
			float dx = lengthX / length;
			float dy = lengthY / length;
			float dz = lengthZ / length;

			float curX = float(start.x);
			float curY = float(start.y);
			float curZ = float(start.z);
			int rayLanght = int(std::roundf(length));
			for (int i = 0; i < rayLanght; ++i) {
				int curZInt = int(std::roundf(curZ));
				if(curZInt == z && arr.getArray2d(z).isEmpty())
					break;
				T item = arr.get(int(std::roundf(curX)), int(std::roundf(curY)), curZInt);
				if (item != arr.getBackground()) {
					plane.set(Point(x, z), item);
					break;
				}
				curX += dx;
				curY += dy;
				curZ += dz;
			}
		}
	}
	return plane;
}

template<typename T>
inline void Tool3d::setLightYZ(Array3d<T>& arr, T light)
{
	for (int z = 0; z < arr.getSize().z; ++z) {
		for (int y = 0; y < arr.getSize().y; ++y) {
			for (int x = 0; x < arr.getSize().x; ++x) {
				if (arr.get(Point3d(x, y, z)) != arr.getBackground()) {
					arr.set(Point3d(x, y, z), light);
					break;
				}
			}
		}
	}
}

template <typename T>
inline void Tool3d::setCuboid(Array3d<T> &arr, Area3d area, T brush, T fill) {
	for (int z = area.position.z; z < area.position.z + area.size.z; ++z) {
		if (z > 0 && z < arr.getSize().z) {
			Area area2d = Area(Point(area.position.x, area.position.y), Size(area.size.x, area.size.y));
			Tool2d::setRectangle(arr.getArray2d(z), area2d, brush, fill);
		}
	}
}

template <typename T>
inline void Tool3d::setCylinder(Array3d<T> &arr, Area3d area, T brush) {
	for (int z = area.position.z; z < area.position.z + area.size.z; ++z) {
		Tool2d::setCircle(arr.getArray2d(z), Point(area.position.x, area.position.y), area.size.x / 2, brush);
	}

}

template<typename T>
inline void Tool3d::setBall(Array3d<T>& arr, Area3d area, T brush)
{
	for (int z = 0; z < area.size.z; ++z) {
		for (int y = 0; y < area.size.y; ++y) {
			for (int x = 0; x < area.size.x; ++x) {
				Point3d realPosition = Point3d(area.position.x + x, area.position.y + y, area.position.z + z);
				float x1 = x - 0.5 * area.size.x;
				float y1 = y - 0.5 * area.size.y;
				float z1 = z - 0.5 * area.size.z;
				float ellipse = (x1*x1) / (area.size.x * area.size.x) + (y1*y1) / (area.size.y * area.size.y) + (z1*z1) / (area.size.z * area.size.z);
				if (arr.isInside(realPosition) 
					&& ellipse < 0.24
					&& ellipse > 0.1) {
					arr.set(realPosition, brush);
				}
				//if(x == area.size.x - 1 || y == area.size.y - 1 || x==0 || y==0 )
				//	arr.set(realPosition, brush);
			}
		}
	}
}

template <typename T>
inline void Tool3d::setLine(Array3d<T> &arr, Point3d start, Point3d end, T brush) {
	int lengthX = end.x - start.x;
	int lengthY = end.y - start.y;
	int lengthZ = end.z - start.z;
	
	float length = sqrt(pow(abs(lengthX), 2) + pow(abs(lengthY), 2) + pow(abs(lengthY), 2));
	if (length == 0.0f)
		return;
	float dx = lengthX / length;
	float dy = lengthY / length;
	float dz = lengthZ / length;
	
	float x = float(start.x);
	float y = float(start.y);
	float z = float(start.z);
	for (int i = 0; i < int(std::roundf(length)); ++i) {
		arr.set(int(std::roundf(x)), int(std::roundf(y)), int(std::roundf(z)), brush);
		x += dx;
		y += dy;
		z += dz;
	}

}

template <typename T>
inline void Tool3d::setPoint(Array3d<T> &arr, Point3d start, T brush) {

}
////////////////////////////////////

