/*  Geoffrey Murray
 *  This class controls the 
 *  all input from keyboard,
 *  mouse, gamepad, etc.
 */

#ifndef INPUT_H
#define INPUT_H
#include "Camera.h"
 
/* GLUT */
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


#define MOUSE_BUTTON_PRESSED    0
#define MOUSE_BUTTON_UNPRESSED  1

#define GLUT_LEFT_MOUSE    0
#define GLUT_MIDDLE_MOUSE  1
#define GLUT_RIGHT_MOUSE   2
#define GLUT_WHEEL_UP      3
#define GLUT_WHEEL_DOWN    4

class Input {
private:
	int x_pressed;
	int y_pressed;
	int buttonPressed;
	Camera* userCamera;
	Camera* userCameraTop;

public:
	Input(Camera* Cam, Camera* CameraTop);
	~Input();

	/* Handles all key presses */
	void handleKeypress(unsigned char key, int x, int y);

	/*  Handles all mouse functionality */
	void processMouse(int button, int state, int x, int y);

	/* Handles all motion when a mouse button is pressed */
	void processMotion(int x, int y);

};
#endif