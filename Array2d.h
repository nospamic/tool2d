#pragma once

class Point 
{
public:
	Point(int x, int y) : x(x), y(y) {
	}
	bool operator ==(const Point&other) {
		return (x == other.x && y == other.y);
	}
	bool operator !=(const Point&other) {
		return !(x == other.x && y == other.y);
	}
	void operator = (const Point &other) {
		x = other.x;
		y = other.y;
	}
	int x, y;
};

class Size
{
public:
	Size():x(0), y(0) {
	}
	Size(int x, int y) : x(x), y(y) {
	}
	bool operator ==(const Size&other) {
		return (x == other.x && y == other.y);
	}
	bool operator !=(const Size&other) {
		return !(x == other.x && y == other.y);
	}
	void operator = (const Size &other) {
		x = other.x;
		y = other.y;
	}
	int x, y;
};
////////////////////////////////////////////////////////

template <typename T>
class Array2d
{
public:
	Array2d(Size size);
	Array2d(const Array2d<T> &other);
	Array2d(Array2d<T> &&other);
	Array2d<T>& operator=(const Array2d<T> &other);
	Array2d<T>& operator=(Array2d<T> &&other);
	~Array2d();
	
	void fill(T item);
	void fill();
	T get(Point point) const;
	T get(int x, int y) const;
	void set(Point point, T item);
	void set(int x, int y, T item);
	Size getSize() const;
	void SetBackground(T background);
	T getBackground() const;
	bool isInside(Point point) const;

protected:
	Size size;
	T **base;
	T background;

private:
	
};


template <typename T>
Array2d<T>::Array2d(Size size) :size(size) {
	std::cout << "Constr:" << size.x << " x " << size.y << "\n";
	base = new T*[size.x];
	for (int i = 0; i < size.x; ++i)
		base[i] = new T[size.y];
}

template <typename T>
Array2d<T>::Array2d(const Array2d<T> &other) {
	std::cout << "copy constr:" << size.x << " x " << size.y << "\n";
	size = other.size;
	base = new T*[size.x];
	for (int i = 0; i < size.x; ++i)
		base[i] = new T[size.y];
	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y)
			base[x][y] = other.base[x][y];
	}
}

template <typename T>
Array2d<T>::Array2d(Array2d<T> &&other) :base(other.base) {
	std::cout << "move constr:" << size.x << " x " << size.y << "\n";
	size = other.size;
	other.size = Size(0, 0);
	other.base = nullptr;

}

template <typename T>
Array2d<T>& Array2d<T>::operator=(const Array2d<T> &other) {
	std::cout << "copy assigment:" << size.x << " x " << size.y << "\n";
	if (&other == this)
		return *this;
	if (size != other.size) {
		for (int i = 0; i < size.x; ++i)
			delete[] base[i];
		delete[] base;
		size = other.size;
		base = new T*[size.x];
		for (int i = 0; i < size.x; ++i)
			base[i] = new T[size.y];
	}
	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y)
			base[x][y] = other.base[x][y];
	}
	return *this;
}

template <typename T>
Array2d<T>& Array2d<T>:: operator=(Array2d<T> &&other) {
	std::cout << "move assigment:" << size.x << " x " << size.y << "\n";
	if (&other == this)
		return *this;
	for (int i = 0; i < size.x; ++i)
		delete[] base[i];
	delete[] base;
	size = other.size;
	base = other.base;
	other.size = Size(0, 0);
	other.base = nullptr;
	return *this;
}

template <typename T>
Array2d<T>:: ~Array2d(){
	for (int i = 0; i < size.x; ++i)
		delete[] base[i];
	delete[] base;
}

template <typename T>
void Array2d<T>:: fill(T item) {
	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y)
			base[x][y] = item;
	}
}

template<typename T>
void Array2d<T>::fill(){
	fill(background);
}

template <typename T>
T Array2d<T>::get(Point point)const {
	return base[point.x][point.y];
}

template <typename T>
T Array2d<T>::get(int x, int y) const{
	return base[x][y];
}

template <typename T>
void Array2d<T>::set(Point point, T item) {
	if (isInside(point))
		base[point.x][point.y] = item;
}

template <typename T>
void Array2d<T>::set(int x, int y, T item) {
	if (isInside(Point(x, y)))
		base[x][y] = item;
}

template <typename T>
Size Array2d<T>::getSize() const{
	return size;
}

template<typename T>
void Array2d<T>::SetBackground(T background){
	this->background = background;
}

template<typename T>
T Array2d<T>::getBackground() const{
	return background;
}

template<typename T>
bool Array2d<T>::isInside(Point point) const{
	return (point.x >= 0 && point.y >= 0 && point.x < size.x && point.y < size.y);
}
