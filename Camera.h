/*  Geoffrey Murray
 *  This class controls the 
 *  main apllication camera.
 */

#ifndef CAMERA_H
#define CAMERA_H
#include <stdlib.h>
using namespace std;

struct CameraT {
	float x;
	float y;
	float z;
};

struct CameraR {
	float x;
	float y;
	float z;
};

class Camera {
private:
	CameraT coodT;
	CameraR coodR;

public:
  Camera(float transX, float transY, float transZ,
  		 float rotX, float rotY, float rotZ);
  ~Camera();

  void translate(float X, float Y, float Z);
  void rotate(float X, float Y, float Z);

  CameraT getCameraPos();
  CameraR getCameraRot();

};
#endif
