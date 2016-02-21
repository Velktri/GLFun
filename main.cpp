#include "Model.h"
#include "Camera.h"
#include "Input.h"

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


Model* mesh;
Camera* userCamera;
Input* userInput;

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



	/* Draw Floor */
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.4f, 0.6f);
	glVertex3f(5.0f, 0.0f, 5.0f);
	glVertex3f(5.0f, 0.0f, -5.0f);
	glVertex3f(-5.0f, 0.0f, -5.0f);
	glVertex3f(-5.0f, 0.0f, 5.0f);
	glEnd();

	/* Draw mesh */
	vector<vector3D> vertexArray = mesh->getVertices();
	/* Draw all the mesh's quads */
	glColor3f(1.0f, 1.0f, 1.0f);
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

/* Top view */
void drawSceneTop() {
	//Clear information from last draw
	glClearColor(0.1f, 0.4f, 0.4f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//  Set Perspective
    glMatrixMode (GL_PROJECTION);
    glOrtho(-1, 1, -1, 1, -2, 2);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	glTranslatef(0.0f, 10.0f, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);

	/* Draw Floor */
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.4f, 0.6f);
	glVertex3f(5.0f, 0.0f, 5.0f);
	glVertex3f(5.0f, 0.0f, -5.0f);
	glVertex3f(-5.0f, 0.0f, -5.0f);
	glVertex3f(-5.0f, 0.0f, 5.0f);
	glEnd();

	vector<vector3D> vertexArray = mesh->getVertices();
	/* Draw all the mesh's quads */
	glColor3f(1.0f, 1.0f, 1.0f);
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
    glutPostRedisplay(); //Tell GLUT that the scene has changed
    
    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
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
		cout << "Please enter an .obj file to be drawn." << endl;
		exit(0);
	}

	/* Main camera for the user */
	userCamera = new Camera(0.0f, 0.0f, -5.0f,
							0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f);

	/* User's Inputs */
	userInput = new Input(userCamera);


	/* Initialize GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(2048, 820); //Set the window size


	
	/* Create the application window */
	int appWindow = glutCreateWindow("My OBJ Viewer");
	initRendering();
	glutDisplayFunc(drawApplication);	

	/* Handles resizing of the main window */
	glutReshapeFunc(handleResize);



	/* Create a sub window for the 3d scene */
	glutCreateSubWindow(appWindow, 0, 100, 1024, 720);
	glutDisplayFunc(drawScene);

	/* Set handler functions keypresses and mouse */
	glutKeyboardFunc(Keypress);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	/* Handles resizing of the window */
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0); //Add a timer



	/* Top view window */
	glutCreateSubWindow(appWindow, 1024, 100, 1024, 720);
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
	if (glewInit() != GLEW_OK)
	{
	    cout << "Failed to initialize GLEW" << endl;
	    return -1;
	}

	glutMainLoop();
	return 0;
}
