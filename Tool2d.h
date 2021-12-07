#ifndef ARRAY2D_H
#define ARRAY2D_H
#include "Array2d.h"




namespace Tool2d
{
	template<typename T>
	void rotate(Array2d<T> &arr, Point center, float alpha);
	template<typename T>
	void setCircle(Array2d<T> &arr, Point upLeft, int radius, T brush);
	template<typename T>
	void setLine(Array2d<T> &arr, Point upLeft, Size size, T brush);
	template<typename T>
	void setRectangle(Array2d<T> &arr, Area area, T brush, T fill);

	//Rotate/////////////////////////////////////////////////////////////
	int round(float a);
	int rotateX(Point point, Point center, float fi);
	int rotateY(Point point, Point center, float fi);
}


template<typename T>
inline void Tool2d::rotate(Array2d<T> &arr, Point center, float alpha) {
	Array2d<T> temp(arr.getSize());
	temp.setBackground(arr.getBackground());
	temp.fill();
	for (int x = 0; x < arr.getSize().x; ++x) {
		for (int y = 0; y < arr.getSize().y; ++y) {
			T current = arr.get(x, y);
			if (current != arr.getBackground()) {
				int xNew = rotateX(Point(x, y), center, alpha);
				int yNew = rotateY(Point(x, y), center, alpha);
				temp.set(xNew, yNew, current);
			}
		}
	}
	arr = std::move(temp);
}



template<typename T>
inline void Tool2d::setCircle(Array2d<T> &arr, Point upLeft, int radius, T brush) {
	Point start(upLeft.x + radius, upLeft.y);
	for (int n = 0; n < 360; n++)
	{
		int x = rotateX(start, Point(start.x, upLeft.y + radius), float(n));
		int y = rotateY(start, Point(start.x, upLeft.y + radius), float(n));
		arr.set(x, y, brush);
	}
}


template<typename T>
inline void Tool2d::setLine(Array2d<T> &arr, Point upLeft, Size size, T brush) {
	float x = float(upLeft.x);
	float y = float(upLeft.y);
	float dx, dy;
	int length = int(sqrt(pow(double(size.x), 2) + pow(double(size.y), 2)));
	dx = float(size.x) / float(length);
	dy = float(size.y) / float(length);
	for (int n = 0; n < length; n++) {
		arr.set(round(x), round(y), brush);
		x += dx;
		y += dy;
	}
}

template<typename T>
inline void Tool2d::setRectangle(Array2d<T> &arr, Area area, T brush, T fill) {
	for (int y = area.position.y; y < area.position.y + area.size.y; ++y) {
		for (int x = area.position.x; x < area.position.x + area.size.x; ++x) {
			if (x > area.position.x 
				&& x < area.position.x + area.size.x - 1 
				&& y > area.position.y 
				&& y < area.position.y + area.size.y - 1) {
				arr.set(x, y, fill);
			}
			else {
				arr.set(x, y, brush);
			}
		}
	}
}


inline int Tool2d::round(float a) {
	return int(std::round(a));
}


inline int Tool2d::rotateX(Point point, Point center, float fi) {
	float x0 = float(center.x);
	float y0 = float(center.y);
	float alpha = fi * 3.1416f / 180.0f;
	float X = x0 + (point.x - x0) * float(cos(double(alpha))) - (point.y - y0) * float(sin(double(alpha)));
	return round(X);
}


inline int Tool2d::rotateY(Point point, Point center, float fi) {
	float x0 = float(center.x);
	float y0 = float(center.y);
	float alpha = fi * 3.1416f / 180.0f;
	float Y = y0 + (point.y - y0) * float(cos(double(alpha))) + (point.x - x0) * float(sin(double(alpha)));
	return round(Y);
}


#endif //ARRAY2D_H