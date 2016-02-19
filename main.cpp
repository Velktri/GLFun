#include "Model.h"
#include "Camera.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define MOUSE_BUTTON_PRESSED    0
#define MOUSE_BUTTON_UNPRESSED  1

#define GLUT_LEFT_MOUSE    0
#define GLUT_MIDDLE_MOUSE  1
#define GLUT_RIGHT_MOUSE   2
#define GLUT_WHEEL_UP      3
#define GLUT_WHEEL_DOWN    4

Model* mesh;
Camera* userCamera;
float _angle = 2.0f;
int x_pressed = 0;
int y_pressed = 0;
int buttonPressed = -1;

/* Handles all key presses */
void handleKeypress(unsigned char key, int x, int y) {
	/* Primative camera movements */
	if (key == 'e') {
		userCamera->translate(0.0f, 1.0f, 0.0f);
	} else if (key == 'q') {
		userCamera->translate(0.0f, -1.0f, 0.0f);
	} else if (key == 'f') {
		userCamera->set();
	} else if (key == 'd') {
		userCamera->translate(-1.0f, 0.0f, 0.0f);
	}
}

/*  Handles all mouse functionality */
void processMouse(int button, int state, int x, int y) {

	if (state == MOUSE_BUTTON_PRESSED) {
		/* Camera Scaling */
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
void processMotion(int x, int y) {
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

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   0.01,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
}











/* Draw functions for all windows */
void drawApplication() {


}

/* Draws the 3D scene sub window */
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	/* Apply camera transforms */
	vector3D userPos = userCamera->getCameraPos();
	glTranslatef(userPos.x, userPos.y, userPos.z);

	/*  Apply camera rotations */
	vector3D userRot = userCamera->getCameraRot();
    glRotatef (userRot.x, 1.0f, 0.0f, 0.0f);
    glRotatef (userRot.y, 0.0f, 1.0f, 0.0f);
    glRotatef (userRot.z, 0.0f, 0.0f, 1.0f);

	vector<vector3D> vertexArray = mesh->getVertices();

	/* Draw all the mesh's quads */
	glBegin(GL_QUADS);
	vector<FaceData> quadArray = mesh->getQuads();
	for (unsigned int i = 0; i < quadArray.size(); i++) {
		int quadSize = quadArray.at(0).vertexPoint.size();
		for (int j = 0; j < quadSize; ++j) {
			glVertex3f(vertexArray.at(quadArray.at(i).vertexPoint.at(j) - 1).x, 
					   vertexArray.at(quadArray.at(i).vertexPoint.at(j) - 1).y, 
					   vertexArray.at(quadArray.at(i).vertexPoint.at(j) - 1).z);
		}
	}
	glEnd();

	/* Draw all the mesh's triangles */
	vector<FaceData> triArray = mesh->getTris();
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < triArray.size(); i++) {
		int triSize = triArray.at(0).vertexPoint.size();
		for (int j = 0; j < triSize; ++j) {
			glVertex3f(vertexArray.at(triArray.at(i).vertexPoint.at(j) - 1).x, 
					   vertexArray.at(triArray.at(i).vertexPoint.at(j) - 1).y, 
					   vertexArray.at(triArray.at(i).vertexPoint.at(j) - 1).z);
		}
	}
	glEnd();
	vertexArray.clear();
	quadArray.clear();
	triArray.clear();

	glutSwapBuffers(); //Send the 3D scene to the screen
}








void update(int value) {
    /*_angle += 2.0f;
    if (_angle > 360) {
        _angle -= 360;
    }
    
    glutPostRedisplay(); //Tell GLUT that the scene has changed*/
    
    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
}









int main(int argc, char** argv) {
	/* Check the args and open up the model */
	if (argc == 2) {
		std::string fileName(argv[1]);
		mesh = new Model(fileName);
	} else {
		cout << "Please enter an .obj file to be drawn." << endl;
		exit(0);
	}

	/* Main camera for the user */
	userCamera = new Camera(0.0f, 0.0f, -5.0f,
							0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f);


	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 820); //Set the window size


	
	/* Create the application window */
	int appWindow = glutCreateWindow("My OBJ Viewer");
	glutDisplayFunc(drawApplication);	

	/* Handles resizing of the main window */
	glutReshapeFunc(handleResize);



	/* Create a sub window for the 3d scene */
	glutCreateSubWindow(appWindow, 0, 100, 1024, 720);
	initRendering();
	glutDisplayFunc(drawScene);

	/* Set handler functions keypresses and mouse */
	glutKeyboardFunc(handleKeypress);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMotion);

	/* Handles resizing of the window */
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0); //Add a timer

	/* Initialize GLEW */
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
	    cout << "Failed to initialize GLEW" << endl;
	    return -1;
	}

	glutMainLoop();
	return 0;
}
