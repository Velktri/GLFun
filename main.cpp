/* GLEW */
#define GLEW_STATIC
#include <GL/glew.h>

#include "Model.h"
#include "Camera.h"
#include "Input.h"
#include "Draw.h"


Model* mesh;
Camera* userCamera;
Input* userInput;
Draw* Scene;


//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
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
				   0.1,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
}






void update(int value) {
    glutPostRedisplay(); //Tell GLUT that the scene has changed
    
    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
}








/* Drawing Handlers */
void drawApp() {
	Scene->drawApplication();
}

void drawScene() {
	Scene->drawScene();
}

void drawSceneTop() {
	Scene->drawSceneTop();
}


/* Input Handlers */
void Keypress(unsigned char key, int x, int y) {
	userInput->handleKeypress(key, x, y);
}

void Mouse(int button, int state, int x, int y) {
	userInput->processMouse(button, state, x, y);
}

void Motion(int x, int y) {
	userInput->processMotion(x, y);
}


int main(int argc, char** argv) {
	/* Check the args and open up the model */
	if (argc == 2) {
		std::string fileName(argv[1]);
		mesh = new Model(fileName);
	} else {
		std::cout << "Please enter an .obj file to be drawn." << std::endl;
		exit(0);
	}

	/* Main camera for the user */
	userCamera = new Camera(0.0f, 0.0f, -5.0f,
							0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f);

	/* User's Inputs */
	userInput = new Input(userCamera);

	/* Create the Scene */
	Scene = new Draw(userCamera, mesh);


	/* Initialize GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(2048, 820); //Set the window size


	
	/* Create the application window */
	int appWindow = glutCreateWindow("My OBJ Viewer");
	initRendering();
	glutDisplayFunc(drawApp);

	/* Handles resizing of the main window */
	glutReshapeFunc(handleResize);




	/* Create a sub window for the 3d scene */
	glutCreateSubWindow(appWindow, 0, 100, 1024, 720);
	initRendering();
	glutDisplayFunc(drawScene);

	/* Set handler functions keypresses and mouse */
	glutKeyboardFunc(Keypress);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	/* Handles resizing of the window */
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0); //Add a timer



	/* Top view sub window */
	glutCreateSubWindow(appWindow, 1024, 100, 1024, 720);
	initRendering();
	glutDisplayFunc(drawSceneTop);

	/* Set handler functions keypresses and mouse */
	glutKeyboardFunc(Keypress);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	/* Handles resizing of the window */
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0); //Add a timer	

	/* Initialize GLEW */
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
	    std::cout << "Failed to initialize GLEW" << std::endl;
	    return -1;
	}

	glutMainLoop();
	return 0;
}