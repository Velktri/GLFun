#include "Camera.h"

Camera::Camera(float transX, float transY, float transZ,
			   float rotX, float rotY, float rotZ) {

	coodT.x = transX;
	coodT.y = transY;
	coodT.z = transZ;

	coodR.x = rotX;
	coodR.y = rotY;
	coodR.z = rotZ;

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

CameraT Camera::getCameraPos() {
	return coodT;
}

CameraR Camera::getCameraRot() {
	return coodR;
}

