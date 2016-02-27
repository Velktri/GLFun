/* GLEW */
#define GLEW_STATIC
#include <GL/glew.h>

#include "Model.h"
#include "Camera.h"
#include "Input.h"
#include "Draw.h"

#define WINDOW_SIZE_X 450
#define WINDOW_SIZE_Y 450

Model* mesh;

Camera* userCameraPerspective;
Camera* userCameraOrtho;

Input* userInput;
Input* userInputTop;

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

//Called when the window is resized
void handleResizeOrtho(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(0.0,                  //The camera angle
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

void drawSceneSide() {
	Scene->drawSceneSide();
}

void drawSceneFront() {
	Scene->drawSceneFront();
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


/* Generates a subwindow */ 
void GenerateWindow(int sceneType, int window, int positionX, int positionY, int dimensionX, int dimensionY) {
	/* Create a sub window for the 3d scene */
	glutCreateSubWindow(window, positionX, positionY, dimensionX, dimensionY);
	initRendering();
	if (sceneType == 1) {
		glutDisplayFunc(drawScene);
	} else if (sceneType == 2) {
		glutDisplayFunc(drawSceneTop);	
	} else if (sceneType == 3) {
		glutDisplayFunc(drawSceneSide);	
	} else if (sceneType == 4) {
		glutDisplayFunc(drawSceneFront);	
	}

	/* Set handler functions keypresses and mouse */
	glutKeyboardFunc(Keypress);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	/* Handles resizing of the window */
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0); //Add a timer
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

	/* Main Perspective camera for the user */
	userCameraPerspective = new Camera(0.0f, 0.0f, -12.0f,
							0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f);

	/* Main Orthographic camera for the user */
	userCameraOrtho = new Camera(0.5f, -0.5f, -0.5f,
							0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f);

	/* User's Inputs */
	userInput = new Input(userCameraPerspective, userCameraOrtho);

	/* Create the Scene */
	Scene = new Draw(userCameraPerspective, userCameraOrtho, mesh);


	/* Initialize GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(900, 950);


	
	/* Create the application window */
	int appWindow = glutCreateWindow("Geo Viewer");
	initRendering();
	glutDisplayFunc(drawApp);

	/* Handles resizing of the main window */
	glutReshapeFunc(handleResize);

	/* Generate 4 windows */
	int sceneType = 1;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			GenerateWindow(sceneType, appWindow, 
						   j * WINDOW_SIZE_X, 50 + (i * WINDOW_SIZE_Y),
						   WINDOW_SIZE_X, WINDOW_SIZE_Y);
			sceneType++;
		}
	}

	/* Initialize GLEW */
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
	    std::cout << "Failed to initialize GLEW" << std::endl;
	    return -1;
	}

	glutMainLoop();
	return 0;
}