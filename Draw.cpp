#include "Draw.h"

Draw::Draw(Camera* Cam, Model* mod) {
	userCamera = Cam;
	mesh = mod;
}

Draw::~Draw() {

}

void Draw::drawApplication() {


}

void Draw::drawScene() {
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
	drawGrid(10, 1, 1);

	/* Draw mesh */
	std::vector<vector3D> vertexArray = mesh->getVertices();
	/* Draw all the mesh's quads */
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	std::vector<FaceData> quadArray = mesh->getQuads();
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
	std::vector<FaceData> triArray = mesh->getTris();
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



void Draw::drawSceneTop() {
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
	drawGrid(10, 1, 1);

	std::vector<vector3D> vertexArray = mesh->getVertices();
	/* Draw all the mesh's quads */
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	std::vector<FaceData> quadArray = mesh->getQuads();
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
	std::vector<FaceData> triArray = mesh->getTris();
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

void Draw::drawGrid(int gridLines, int gridSpacing, int xyzFLAG) {
	int	colorY = 0;
	int	colorX = 0;
	int	colorZ = 0;

	glBegin(GL_LINES);
	if (xyzFLAG & 1) {
		/* XZ */
		colorZ = 1;
		colorX = 1;

		for (int i = -gridLines; i <= gridLines; i++) {
			/* X lines */
			if (i != 0) {	
				glVertex3f(i, 0.0f, -gridLines);
				glVertex3f(i, 0.0f, gridLines);

				/* Z lines */
				glVertex3f(-gridLines, 0.0f, gridSpacing * i);
				glVertex3f(gridLines, 0.0f, gridSpacing * i);
			}
		}
	}

	if (xyzFLAG & 2) {
		/* YX */
		colorY = 1;
		colorX = 1;

		for (int i = -gridLines; i <= gridLines; i++) {
			/* Y lines */
			if (i != 0) {
				glVertex3f(i, -gridLines, 0.0f);
				glVertex3f(i, gridLines, 0.0f);

				/* X lines */
				glVertex3f(-gridLines, gridSpacing * i, 0.0f);
				glVertex3f(gridLines, gridSpacing * i, 0.0f);
			}
		}
	}

	if (xyzFLAG & 4) {
		/* YZ */
		colorY = 1;
		colorZ = 1;

		for (int i = -gridLines; i <= gridLines; i++) {
			/* Y lines */
			if (i != 0) {	
				glVertex3f(0.0f, i, -gridLines);
				glVertex3f(0.0f, i, gridLines);

				/* Z lines */
				glVertex3f(0.0f, -gridLines, gridSpacing * i);
				glVertex3f(0.0f, gridLines, gridSpacing * i);
			}
		}
	}

	/* X */
	if (colorX) {
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-gridLines, 0.0f, 0.0f);
		glVertex3f(gridLines, 0.0f, 0.0f);
	}

	/* Y */
	if (colorY) {
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -gridLines, 0.0f);
		glVertex3f(0.0f, gridLines, 0.0f);
	}

	/* Z */
	if (colorZ) {
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -gridLines);
		glVertex3f(0.0f, 0.0f, gridLines);
	}
	glEnd();
}