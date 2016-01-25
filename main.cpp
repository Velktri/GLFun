#include "Model.h"

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Model* mesh;

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
					int x, int y) {    //The current mouse coordinates
	switch (key) {
		case 27: //Escape key
			exit(0); //Exit the program
	}
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

//Draws the 3D scene
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	glBegin(GL_QUADS); //Begin quadrilateral coordinates
	
  vector<vector3D> vertexArray = mesh->getVertices();
  for (unsigned int i = 0; i < vertexArray.size(); i++) {
    glVertex3f(vertexArray.at(i).x, vertexArray.at(i).y, vertexArray.at(i).z);
    cout << vertexArray.at(i).x << " " << vertexArray.at(i).y << " " << vertexArray.at(i).z << endl;
  }
	/* Trapezoid
	glVertex3f(-0.7f, -1.5f, -5.0f);
	glVertex3f(0.7f, -1.5f, -5.0f);
	glVertex3f(0.4f, -0.5f, -5.0f);
	glVertex3f(-0.4f, -0.5f, -5.0f); */
	
	glEnd(); //End quadrilateral coordinates
	
  glutSwapBuffers(); //Send the 3D scene to the screen
}

int main(int argc, char** argv) {
  /* Open up the model */
  if (argc == 2) {
    std::string fileName(argv[1]);
    mesh = new Model(fileName);
    mesh->myPrint();
  }

	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 720); //Set the window size
	
	//Create the window
	glutCreateWindow("My OBJ Viewer");
	initRendering(); //Initialize rendering
	
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}
