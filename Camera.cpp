#include "Camera.h"

Camera::Camera(float transX, float transY, float transZ,
			   float rotX, float rotY, float rotZ,
			   float focusX, float focusY, float focusZ) {

	coodT.x = transX;
	coodT.y = transY;
	coodT.z = transZ;

	coodR.x = rotX;
	coodR.y = rotY;
	coodR.z = rotZ;

	/* Focus point for camera */
	focusT.x = focusX;
	focusT.y = focusY;
	focusT.z = focusZ;
}

Camera::~Camera() {

}

void Camera::translate(float X, float Y, float Z) {
	coodT.x += X;
	coodT.y += Y;
	coodT.z += Z;
}

void Camera::rotate(float X, float Y, float Z) {
	coodR.x += X;
	coodR.y += Y;
	coodR.z += Z;
}

void Camera::pan(int deltaX, int deltaY) {

}

void Camera::orbit(int deltaX, int deltaY) {
	float focusDist = this->getDistance();

}

float Camera::getDistance() {
	return sqrt(pow((coodT.x + focusT.x), 2) + pow((coodT.y + focusT.y), 2) + pow((coodT.z + focusT.z), 2));
}

/* Getters */
vector3D Camera::getCameraPos() {
	return coodT;
}

vector3D Camera::getCameraRot() {
	return coodR;
}