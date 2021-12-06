#pragma once
#include "Array2d.h"



template <typename T>
class Tool2d :
	public Array2d<T>
{
public:
	Tool2d();
	Tool2d(Size size);
	Tool2d(Size size, T background);
	~Tool2d();

	void rotate(Point center, float alpha);
	void setCircle(Point upLeft, int radius, T brush);
	void setLine(Point upLeft, Size size, T brush);
	void setRectangle(Point upLeft, Size size, T brush, T fill);

private:
	//Rotate/////////////////////////////////////////////////////////////
	int round(float a);
	int rotateX(Point point, Point center, float fi);
	int rotateY(Point point, Point center, float fi);
};

template<typename T>
inline Tool2d<T>::Tool2d(): Array2d<T>(Size(0, 0))
{
}

template <typename T>
Tool2d<T>:: Tool2d(Size size):Array2d<T>(size) {

}

template<typename T>
inline Tool2d<T>::Tool2d(Size size, T background) : Array2d<T>(size){
	Array2d<T>::setBackground(background);
	Array2d<T>::fill();
}

template<typename T>
inline Tool2d<T>::~Tool2d(){
}

template<typename T>
void Tool2d<T>::rotate(Point center, float alpha) {
	Tool2d<T> temp(Array2d<T>::size);
	temp.setBackground(Array2d<T>::background);
	temp.fill();
	for (int x = 0; x < Array2d<T>::size.x; ++x) {
		for (int y = 0; y < Array2d<T>::size.y; ++y)
			if (Array2d<T>::base[x][y] != Array2d<T>::background) {
				int xNew = rotateX(Point(x, y), center, alpha);
				int yNew = rotateY(Point(x, y), center, alpha);
				temp.set(xNew, yNew, Array2d<T>::base[x][y]);
			}
	}
	*this = std::move(temp);
}

template<typename T>
inline void Tool2d<T>::setCircle(Point upLeft, int radius, T brush) {
	Point start(upLeft.x + radius, upLeft.y);
	for (int n = 0; n < 360; n++)
	{
		int x = rotateX(start, Point(start.x, upLeft.y + radius), float(n));
		int y = rotateY(start, Point(start.x, upLeft.y + radius), float(n));
		Tool2d<T>::set(x, y, brush);
	}
}

template<typename T>
inline void Tool2d<T>::setLine(Point upLeft, Size size, T brush) {
	float x = float(upLeft.x);
	float y = float(upLeft.y);
	float dx, dy;
	int length = int(sqrt(pow(double(size.x), 2) + pow(double(size.y), 2)));
	dx = float(size.x) / float(length);
	dy = float(size.y) / float(length);
	for (int n = 0; n < length; n++) {
		Array2d<T>::set(round(x), round(y), brush);
		x += dx;
		y += dy;
	}
}

template<typename T>
void Tool2d<T>::setRectangle(Point upLeft, Size size, T brush, T fill) {
	for (int y = upLeft.y; y < upLeft.y + size.y; ++y) {
		for (int x = upLeft.x; x < upLeft.x + size.x; ++x) {
			if (x > upLeft.x && x < upLeft.x + size.x - 1 && y > upLeft.y && y < upLeft.y + size.y - 1) {
				Tool2d<T>::set(x, y, fill);
			}
			else {
				Tool2d<T>::set(x, y, brush);
			}
		}
	}
}

template<typename T>
inline int Tool2d<T>::round(float a) {
	return int(std::round(a));
}

template<typename T>
int Tool2d<T>::rotateX(Point point, Point center, float fi) {
	float x0 = float(center.x);
	float y0 = float(center.y);
	float alpha = fi * 3.1416f / 180.0f;
	float X = x0 + (point.x - x0) * float(cos(double(alpha))) - (point.y - y0) * float(sin(double(alpha)));
	return round(X);
}

template<typename T>
inline int Tool2d<T>::rotateY(Point point, Point center, float fi) {
	float x0 = float(center.x);
	float y0 = float(center.y);
	float alpha = fi * 3.1416f / 180.0f;
	float Y = y0 + (point.y - y0) * float(cos(double(alpha))) + (point.x - x0) * float(sin(double(alpha)));
	return round(Y);
}
