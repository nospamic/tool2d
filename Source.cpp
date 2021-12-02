#include<iostream>
#include"Tool2d.h"
#include"Dynarry.h"


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

	
	Tool2d<char> arr(Size(30, 20));
	arr.SetBackground('.');
	arr.fill();
	arr.setCircle(Point(10, 2), 12, '@');
	arr.setRectangle(Point(6, 8), Size(16, 9), '0', '*');
	arr.rotate(Point(15, 3), 20);
	Tool2d<char> arr2 = arr;
	show(arr2);
	
	std::cout << "\n";
	system("pause");
	return 0;
	
}