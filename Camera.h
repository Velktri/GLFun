/*  Geoffrey Murray
 *  This class controls the 
 *  main apllication camera.
 */

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
  Camera(float transX, float transY, float transZ);
  ~Camera();

  void translate(float x, float y, float z);
  void rotate(float x, float, y, float z);
};


#endif
