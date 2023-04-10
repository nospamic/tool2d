#ifndef ARRAY2D_H
#define ARRAY2D_H
#include "array2d.h"
#include <math.h>
#include <memory>



namespace Tool2d
{
	template<typename T>
	void rotate(Array2d<T> &arr, Point center, float alpha);
	template<typename T>
	void setCircle(Array2d<T> &arr, Point upLeft, int radius, T brush);
	template<typename T>
	void setLine(Array2d<T> &arr, Point start, Point end, T brush);
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
//#pragma omp parallel for
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
inline void Tool2d::setLine(Array2d<T> &arr, Point start, Point end, T brush) {
	int lengthX = end.x - start.x;
	int lengthY = end.y - start.y;

	float length = sqrt(pow(abs(lengthX), 2) + pow(abs(lengthY), 2));
	if (length == 0.0f)
		return;
	float dx = lengthX / length;
	float dy = lengthY / length;

	float x = float(start.x);
	float y = float(start.y);
	for (int i = 0; i < int(myRound(length)); ++i) {
		arr.set(int(myRound(x)), int(myRound(y)), brush);
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


inline int Tool2d::round(float n) {
	if (n == 0) return 0;
	return n > 0 ? (int)(n + 0.5f) : (int)(n - 0.5f);
}


inline int Tool2d::rotateX(Point point, Point center, float fi) {
	float x0 = float(center.x);
	float y0 = float(center.y);
	float alpha = fi * 0.01745f;//3.14/180
	float X = x0 + (point.x - x0) * cosf(alpha) - (point.y - y0) * sinf(alpha);
	return (int)(X + 0.5f);
}


inline int Tool2d::rotateY(Point point, Point center, float fi) {
	float x0 = float(center.x);
	float y0 = float(center.y);
	float alpha = fi * 0.01745f;//3.14/180
	float Y = y0 + (point.y - y0) * cosf(alpha) + (point.x - x0) * sinf(alpha);
	return (int)(Y + 0.5f);
}


#endif //ARRAY2D_H