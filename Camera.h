/*  Geoffrey Murray
 *  This class controls the 
 *  main application camera.
 */

#ifndef CAMERA_H
#define CAMERA_H
#include <stdlib.h>
#include "utils.h"
#include <iostream>
using namespace std;

struct quaternion {
	float w;
	float x;
	float y;	
	float z;
};

class Camera {
private:
	vector3D coodT;
	vector3D coodR;
	vector3D focusT;
	quaternion quat;

	float getDistance();

public:
  Camera(float transX, float transY, float transZ,
  		 float rotX, float rotY, float rotZ,
		 float focusX, float focusY, float focusZ);
  ~Camera();

  void translate(float X, float Y, float Z);
  void rotate(float X, float Y, float Z);
  void set();
  void pan(int startX, int startY);
  void orbit(int startX, int startY);

  vector3D getCameraPos();
  vector3D getCameraRot();

};
#endif
