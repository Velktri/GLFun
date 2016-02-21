#include "Input.h"

Input::Input(Camera* Cam) {
	x_pressed = 0;
	y_pressed = 0;
	buttonPressed = -1;
	userCamera = Cam;
}

Input::~Input() {

}

/* Handles all key presses */
void Input::handleKeypress(unsigned char key, int x, int y) {
	/* Focus camera at a point */
	if (key == 'f') {
		userCamera->set();
	} else if(key == 27) {
		glutLeaveMainLoop();//exit(0);
	}
}

/*  Handles all mouse functionality */
void Input::processMouse(int button, int state, int x, int y) {

	if (state == MOUSE_BUTTON_PRESSED) {
		/* Camera Zooming */
		if (button == GLUT_WHEEL_UP) {
			userCamera->translate(0.0f, 0.0f, 1.0f);
		} else if(button == GLUT_WHEEL_DOWN) {
			userCamera->translate(0.0f, 0.0f, -1.0f);
		}

		/* Camera Movement */
		if (button == GLUT_LEFT_MOUSE) {
			buttonPressed = GLUT_LEFT_MOUSE;
			x_pressed = x;
			y_pressed = y;
		} else if (button == GLUT_MIDDLE_MOUSE) {
			buttonPressed = GLUT_MIDDLE_MOUSE;
			x_pressed = x;
			y_pressed = y;
		}
	}
}

/* Handles all motion when a mouse button is pressed */
void Input::processMotion(int x, int y) {
	if (buttonPressed == GLUT_LEFT_MOUSE) {
		int dx = x - x_pressed;
		int dy = y - y_pressed;
		userCamera->pan(dx, dy);
	} else if (buttonPressed == GLUT_MIDDLE_MOUSE) {
		int dx = x - x_pressed;
		int dy = y - y_pressed;
		userCamera->orbit(dx, dy);
	}
	x_pressed = x;
	y_pressed = y;
}