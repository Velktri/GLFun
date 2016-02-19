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

	/* Initialize the quaternion */
	quat.w = 1;
	quat.x = transX;
	quat.y = transY;	
	quat.z = transZ;
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

}

void Camera::pan(int deltaX, int deltaY) {
	coodT.x += (deltaX * -0.001f);
	coodT.y += (deltaY * 0.001f);
}

void Camera::orbit(int deltaX, int deltaY) {
	/*float focusDist = this->getDistance();
	float angle = asin(1 / focusDist) * M_PI * 18;
	//float newDZ = focusDist - ((cos(asin(deltaX / focusDist)) * M_PI * 180) / focusDist);
	cout << cos(asin(deltaX / focusDist)) / focusDist << endl;
	cout << angle << endl;
	//cout << newDZ << endl;

	coodT.x += deltaX;
	coodT.z -= 0.1010205144;//newDZ;
	coodR.y -= angle;
*/

	float angle = 3.7;
	float newY = .1;
	if (deltaX > 0) {
		coodT.x += .3;
		coodT.z += newY;
		coodR.y += angle;
	} else {
		coodT.x -= .3;
		coodT.z -= newY;
		coodR.y -= angle;
	}

	cout << endl;
	cout << coodT.x << " " << coodT.y << " " << coodT.z << endl;
	cout << coodR.x << " " << coodR.y << " " << coodR.z << endl;
	cout << endl;


	/*quaternion* q = &quat;
	float magnitude = (pow(quat.w, 2) + pow(quat.x, 2) + pow(quat.y, 2) + pow(quat.z, 2));

	if (magnitude < 1.1 && magnitude > 0.9) {
		
	} else {
		normalize(q, magnitude);
	}*/
}

void Camera::normalize(quaternion* Q, float magnitude) {
	magnitude = sqrt(magnitude);
	Q->w /= magnitude;
	Q->x /= magnitude;
	Q->y /= magnitude;
	Q->z /= magnitude;	

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