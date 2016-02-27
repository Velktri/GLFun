#include "Input.h"
#include <iostream>

Input::Input(Camera* Cam, Camera* CameraTop) {
	x_pressed = 0;
	y_pressed = 0;
	buttonPressed = -1;
	userCamera = Cam;
	userCameraTop = CameraTop;
}

Input::~Input() {

}

void Input::handleKeypress(unsigned char key, int x, int y) {
	/* Focus camera at a point */
	if (key == 'f') {
		userCamera->set();
	} else if(key == 27) {
		glutLeaveMainLoop();
	} else if(key == 'e') {
		vector3D camPos = userCameraTop->getCameraPos();
		std::cout << camPos.x << std::endl;
		std::cout << camPos.y << std::endl;
		std::cout << camPos.z << std::endl;
	}
}

void Input::processMouse(int button, int state, int x, int y) {
	int windowID = glutGetWindow();
	if (state == MOUSE_BUTTON_PRESSED) {
		/* Camera Zooming */
		if (button == GLUT_WHEEL_UP) {
			if (windowID == 2) {
				userCamera->translate(0.0f, 0.0f, 1.0f);
			} else if (windowID == 3) {
				userCameraTop->ZoomInOut(-1.0f);
			}
		} else if(button == GLUT_WHEEL_DOWN) {
			if (windowID == 2) {
				userCamera->translate(0.0f, 0.0f, -1.0f);
			} else if (windowID == 3) {
				userCameraTop->ZoomInOut(1.0f);
			}
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

void Input::processMotion(int x, int y) {
	int windowID = glutGetWindow();	
	if (buttonPressed == GLUT_LEFT_MOUSE) {
		int dx = x - x_pressed;
		int dy = y - y_pressed;
		if (windowID == 2) {
			userCamera->pan(dx, dy);
		} else if (windowID == 3) {
			userCameraTop->panTop(dx, dy);
		} else if (windowID == 4) {
			userCameraTop->panSide(dx, dy);
		} else if (windowID == 5) {
			userCameraTop->panFront(dx, dy);
		}
	} else if (buttonPressed == GLUT_MIDDLE_MOUSE) {
		int dx = x - x_pressed;
		int dy = y - y_pressed;
		if (windowID == 2) {
			userCamera->orbit(dx, dy);
		}
	}
	x_pressed = x;
	y_pressed = y;
}