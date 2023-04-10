#pragma once
#include<omp.h>
#include "tool3d.h"

template <class T>
class Camera
{
public:
	Camera();
	Camera(Point3d position, Size screenSize);
	Array2d<T> &getScreen();
	void capture(const Array3d<T>& scene);
	void mooveTo(PointF3d position);
	void rotateHorizontal(float angle);
	void rotateVertical(float angle);
	void moveForward(int distance);
	PointF3d position;
	float getAngle();
	
private:
	
	Array2d<Point3d> vScreen;
	Array2d<Point3d> baseVScreen;
	Array2d<T> screen;
	float angleX;
	float angleZ;
	void setVScreen();
	float rotatePointX(PointF point, PointF center, float fi);
	float rotatePointY(PointF point, PointF center, float fi);
	void rotateX(float angle);
	void rotateZ(float angle);
	
	
};

template<class T>
inline Camera<T>::Camera()
{
}

template<class T>
inline Camera<T>::Camera(Point3d position, Size screenSize) : vScreen(Array2d<Point3d>(screenSize)),
																screen(Array2d<T>(screenSize))
{
	this->position = position;
	setVScreen();
	baseVScreen = vScreen;
	angleX = 0.0f;
	angleZ = 0.0f;
}



template<class T>
inline Array2d<T>& Camera<T>::getScreen()
{
	return screen;
}

template<class T>
inline void Camera<T>::capture(const Array3d<T>& scene)
{
	rotateX(angleX);
	rotateZ(angleZ);
	screen.fill(scene.getBackground());
	short lengthX;
	short lengthY;
	short lengthZ;
	float length;
	float dx;
	float dy;
	float dz;
	float curX;
	float curY;
	float curZ;
	short rayLength;
	short baseLength;
	Point3d currentPoint;
	PointF3d step;
	for (int vY = 0; vY < vScreen.getSize().y; ++vY) {
		for (int vX = 0; vX < vScreen.getSize().x; ++vX) {
			lengthX = vScreen.get(vX, vY).x - myRound(position.x);
			lengthY = vScreen.get(vX, vY).y - myRound(position.y);
			lengthZ = vScreen.get(vX, vY).z - myRound(position.z);
			length = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);
			dx = lengthX / length;
			dy = lengthY / length;
			dz = lengthZ / length;
			curX = position.x;
			curY = position.y;
			curZ = position.z;
			baseLength = myRound(length);
			rayLength = baseLength + baseLength;
			step = PointF3d(dx, dy, dz);
			short i = 0;
			while (i < rayLength) {
				currentPoint = Point3d(myRound(curX), myRound(curY), myRound(curZ));
				const T item = scene.get(currentPoint);
				if (i == baseLength) {
					dx = dx * 6;
					dy = dy * 6;
					dz = dz * 6;
				}
				if (!scene.isInside(currentPoint)) {
					screen.set(vX, vY, scene.getBackground());
					break;
				}
				if (i > baseLength && item != scene.getBackground()) {
					while (true) {
						curX -= step.x;
						curY -= step.y;
						curZ -= step.z;
						currentPoint = Point3d(myRound(curX), myRound(curY), myRound(curZ));
						const T item = scene.get(currentPoint);
						if (item == scene.getBackground()) {
							curX += step.x;
							curY += step.y;
							curZ += step.z;
							currentPoint = Point3d(myRound(curX), myRound(curY), myRound(curZ));
							const T item = scene.get(currentPoint);
							screen.set(vX, vY, item);
							break;
						}
					}
					break;
				}
				if (item != scene.getBackground()) {
					screen.set(vX, vY, item);
					break;
				}
				curX += dx;
				curY += dy;
				curZ += dz;
				++i;
			}
		}
	}

}

template<class T>
inline void Camera<T>::mooveTo(PointF3d position)
{
	this->position = position;
	setVScreen();
}

template<class T>
inline void Camera<T>::rotateHorizontal(float angle)
{
	angleZ = angle;
}

template<class T>
inline void Camera<T>::rotateVertical(float angle)
{
	angleX = angle;
}

template<class T>
inline void Camera<T>::moveForward(int distance)
{
	
	PointF3d newPoint(position.x, position.y + distance, position.z);
	PointF center(position.y, position.z);
	float y = rotatePointX(PointF(newPoint.y, newPoint.z), center, angleX);
	float z = rotatePointY(PointF(newPoint.y, newPoint.z), center, angleX);
	newPoint.y = y;
	newPoint.z = z;
	center = PointF(position.x, position.y);
	float x = rotatePointX(PointF(newPoint.x, newPoint.y), center, angleZ);
	y = rotatePointY(PointF(newPoint.x, newPoint.y), center, angleZ);
	newPoint.x = x;
	newPoint.y = y;
	position = newPoint;
	mooveTo(position);
}

template<class T>
inline float Camera<T>::getAngle()
{
	return angleZ;
}

template<class T>
inline void Camera<T>::rotateX(float angle)
{
	if (abs(angle) < 0.001f) {
		vScreen = baseVScreen;
		return;
	}
	
	PointF center = PointF(position.y, position.z);
	Point3d newPoint;
	for (int y = 0; y < baseVScreen.getSize().y; ++y) {
		for (int x = 0; x < baseVScreen.getSize().x; ++x) {
			int oldX = baseVScreen.get(x, y).y;
			int oldY = baseVScreen.get(x, y).z;
			newPoint.x = baseVScreen.get(x, y).x;
			newPoint.y = myRound(rotatePointX(PointF(oldX, oldY), center, angleX));
			newPoint.z = myRound(rotatePointY(PointF(oldX, oldY), center, angleX));
			vScreen.set(x, y, newPoint);
		}
	}
}

template<class T>
inline void Camera<T>::rotateZ(float angle)
{
	if (abs(angle) < 0.0001f) {
		return;
	}
	PointF center = PointF(position.x, position.y);
	Point3d newPoint;
	for (int y = 0; y < baseVScreen.getSize().y; ++y) {
		for (int x = 0; x < baseVScreen.getSize().x; ++x) {
			int oldX = vScreen.get(x, y).x;
			int oldY = vScreen.get(x, y).y;
			newPoint.x = myRound(rotatePointX(PointF(oldX, oldY), center, angleZ));
			newPoint.y = myRound(rotatePointY(PointF(oldX, oldY), center, angleZ));
			newPoint.z = vScreen.get(x, y).z;
			vScreen.set(x, y, newPoint);
		}
	}
}


template<class T>
inline void Camera<T>::setVScreen()
{
	int distance = vScreen.getSize().x / 2;
	Point3d screenPosition = Point3d(
		myRound(position.x) - (vScreen.getSize().x / 2),
		myRound(position.y) + distance,
		myRound(position.z) - (vScreen.getSize().y / 2));
//#pragma omp parallel for
	for (int z = 0; z < vScreen.getSize().y; ++z) {
		for (int x = 0; x < vScreen.getSize().x; ++x) {
			vScreen.set(x, z, Point3d(screenPosition.x + x, screenPosition.y, screenPosition.z + z));
			baseVScreen.set(x, z, Point3d(screenPosition.x + x, screenPosition.y, screenPosition.z + z));
		}
	}
}

template<class T>
inline float Camera<T>::rotatePointX(PointF point, PointF center, float fi)
{
	float x0 = float(center.x);
	float y0 = float(center.y);
	float alpha = fi * 0.01745f;//3.14/180
	float X = x0 + (point.x - x0) * cosf(alpha) - (point.y - y0) * sinf(alpha);
	return X;
}

template<class T>
inline float Camera<T>::rotatePointY(PointF point, PointF center, float fi)
{
	float x0 = float(center.x);
	float y0 = float(center.y);
	float alpha = fi * 0.01745f;//3.14/180
	float Y = y0 + (point.y - y0) * cosf(alpha) + (point.x - x0) * sinf(alpha);
	return Y;
}




