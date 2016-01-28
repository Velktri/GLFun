#include "Model.h"

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Model* mesh;
float _angle = 0.0f;

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
	glTranslatef(0.0f, 0.0f, -2.0f);

	glRotatef(_angle, 0.0f, 0.0f, 1.0f);

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
	vertexArray.close;
	quadArray.close;
	triArray.close;

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void update(int value) {
    /*_angle += 2.0f;
    if (_angle > 360) {
        _angle -= 360;
    }
    
    glutPostRedisplay(); //Tell GLUT that the scene has changed
    
    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);*/
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
	
	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}
