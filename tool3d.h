#pragma once
#include "Tool2d.h"

class Point3d
{
public:
	Point3d() {}
	Point3d(int x, int y, int z) : x(x), y(y), z(z) {
	}
	bool operator ==(const Point3d&other) {
		return (x == other.x && y == other.y && z == other.z);
	}
	bool operator !=(const Point3d&other) {
		return !(x == other.x && y == other.y && z == other.z);
	}
	void operator = (const Point3d &other) {
		x = other.x;
		y = other.y;
		z = other.z;
	}
	int x, y, z;
};

class Size3d
{
public:
	Size3d() :x(0), y(0), z(0) {
	}
	Size3d(int x, int y, int z) : x(x), y(y), z(z) {
	}
	bool operator ==(const Size3d&other) {
		return (x == other.x && y == other.y && z == other.z);
	}
	bool operator !=(const Size3d&other) {
		return !(x == other.x && y == other.y && z == other.z);
	}
	void operator = (const Size3d &other) {
		x = other.x;
		y = other.y;
		z = other.z;
	}
	int x, y, z;
};

class Area3d
{
public:
	Point3d position;
	Size3d size;
	bool isInside(Point3d point) {
		return (point.x >= position.x
			&& point.y >= position.y
			&& point.z >= position.z
			&& point.x < position.x + size.x
			&& point.y < position.y + size.y
			&& point.z < position.z + size.z
			);
	}
	Area3d() {}
	Area3d(Point3d position, Size3d size) : position(position), size(size) {
	}
};

template<typename T>
class Tool3d
{
public:
	Tool3d(Size3d size);
	Tool3d(const Tool3d<T> &other);
	Tool3d(Tool3d<T> &&other);
	Tool3d<T>& operator=(const Tool3d<T> &other);
	Tool3d<T>& operator=(Tool3d<T> &&other);
	~Tool3d();

	void fill(T item);
	void fill();
	T get(Point3d point) const;
	T get(int x, int y, int z) const;
	void set(Point3d point, T item);
	void set(int x, int y, int z, T item);
	Size3d getSize() const;
	void setBackground(T background);
	T getBackground() const;
	bool isInside(Point3d point) const;
private:
	Tool2d<T>*base;
	Size3d size;
	T background;
};

template <typename T>
Tool3d<T>::Tool3d(Size3d size) :size(size) {
	//std::cout << "Constr:" << size.x << " x " << size.y << "\n";
	base = new Tool2d<T>[size.z];
}

template <typename T>
Tool3d<T>::Tool3d(const Tool3d<T> &other) {
	//std::cout << "copy constr:" << size.x << " x " << size.y << "\n";
	size = other.size;
	base = new Tool2d<T>[size.z];
	for (int z = 0; z < size.z; ++z)
			base[z] = other.base[z];
}

template <typename T>
Tool3d<T>::Tool3d(Tool3d<T> &&other) :base(other.base) {
	//std::cout << "move constr:" << size.x << " x " << size.y << "\n";
	size = other.size;
	other.size = Size3d(0, 0, 0);
	other.base = nullptr;
}

template <typename T>
Tool3d<T>& Tool3d<T>::operator=(const Tool3d<T> &other) {
	//std::cout << "copy assigment:" << size.x << " x " << size.y << "\n";
	if (&other == this)
		return *this;
	if (size != other.size) {
		delete[] base;
		size = other.size;
		base = new Tool2d<T>[size.z];
	}
	for (int z = 0; z < size.z; ++z)
		base[z] = other.base[z];
	return *this;
}

template <typename T>
Tool3d<T>& Tool3d<T>:: operator=(Tool3d<T> &&other) {
	//std::cout << "move assigment:" << size.x << " x " << size.y << "\n";
	if (&other == this)
		return *this;
	delete[] base;
	size = other.size;
	base = other.base;
	other.size = Size3d(0, 0, 0);
	other.base = nullptr;
	return *this;
}

template <typename T>
Tool3d<T>:: ~Tool3d() {
	delete[] base;
}

//////////////////////////////////////

template <typename T>
void Tool3d<T>::fill(T item) {
	for (int z = 0; z < size.z; ++z) 
		base[z].Array2d<T>::fill(item);
}

template<typename T>
void Tool3d<T>::fill() {
	for (int z = 0; z < size.z; ++z)
		base[z].Array2d<T>::fill(background);
}

template <typename T>
T Tool3d<T>::get(Point3d point)const {
	return base[point.z].Array2d<T>::get(point.x, point.y);
}

template <typename T>
T Tool3d<T>::get(int x, int y, int z) const {
	return base[z].Array2d<T>::get(x, y);
}

template <typename T>
void Tool3d<T>::set(Point3d point, T item) {
	if (isInside(point))
		base[point.z].Array2d<T>::set(point.x, point.y, item);
}

template <typename T>
void Tool3d<T>::set(int x, int y, int z, T item) {
	if (isInside(Point3d(x, y, z)))
		base[z].Array2d<T>::set(x, y, item);
}

template <typename T>
Size3d Tool3d<T>::getSize() const {
	return size;
}

template<typename T>
void Tool3d<T>::setBackground(T background) {
	this->background = background;
}

template<typename T>
T Tool3d<T>::getBackground() const {
	return background;
}

template<typename T>
bool Tool3d<T>::isInside(Point3d point) const {
	Area3d area = Area3d(Point3d(0, 0, 0), size);
	return area.isInside(point);
}


