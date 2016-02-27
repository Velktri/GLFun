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

	zoom = 0;
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

void Camera::set() {
	coodT = focusT;
	coodT.z = -5.0f;

	coodR.x = 0.0f;
	coodR.y = 0.0f;
	coodR.z = 0.0f;
}

float Camera::getZoom() {
	return zoom;
}

void Camera::ZoomInOut(float x) {
	zoom += x;
}

void Camera::pan(int deltaX, int deltaY) {
	coodT.x += (deltaX * 0.007f);
	coodT.y += (deltaY * -0.007f);
}

void Camera::panTop(int deltaX, int deltaY) {
	coodT.x += (deltaX * 0.001f);
	coodT.z += (deltaY * -0.001f);
}

void Camera::panSide(int deltaX, int deltaY) {
	coodT.z += (deltaX * -0.001f);
	coodT.y += (deltaY * -0.001f);
}

void Camera::panFront(int deltaX, int deltaY) {
	coodT.x += (deltaX * 0.001f);
	coodT.y += (deltaY * -0.001f);
}


void Camera::orbit(int deltaX, int deltaY) {
    float focusDist = abs(focusT.z) / 180;
	float angle = deltaX / 2;

	/* Orbit horizontally */
	if (deltaX > 0) {
		coodT.x += focusDist;
		coodT.z += focusDist;
		coodR.y += angle;
		if (coodR.y > 360) {
        coodR.y -= 360;
    	}
	} else {
		coodT.x -= focusDist;
		coodT.z -= focusDist;
		coodR.y += angle;
		if (coodR.y < -360) {
        coodR.y += 360;
    	}
	}

	/* Orbit vertically */
    float focusDistY = (abs(focusT.x) / 90) / 1.5;
	float angleY = deltaY / 1.5;
	if (deltaY > 0) {
		coodT.y += focusDistY;
		coodT.z += focusDistY;
		coodR.x += angleY;
		if (coodR.x > 360) {
        coodR.x -= 360;
    	}
	} else {
		coodT.y -= focusDistY;
		coodT.z -= focusDistY;
		coodR.x += angleY;
		if (coodR.x < -360) {
        coodR.x += 360;
    	}
	}
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