/*  Geoffrey Murray
 *  This class controls the 
 *  all input from keyboard,
 *  mouse, gamepad, etc.
 */

#ifndef INPUT_H
#define INPUT_H
#include <stdlib.h>
#include "Camera.h"
using namespace std;

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
public:
	Input(Camera* userCamera);
	~Input();

	void handleKeypress(unsigned char key, int x, int y);
	void processMouse(int button, int state, int x, int y);
	void processMotion(int x, int y);
};
#endif