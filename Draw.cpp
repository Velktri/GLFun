#include "Draw.h"

Draw::Draw(Camera* Cam, Camera* CameraTop, Model* mod) {
	userCamera = Cam;
	userCameraTop = CameraTop;
	mesh = mod;
}

Draw::~Draw() {

}

void Draw::drawApplication() {


}

void Draw::drawScene() {
	glClearColor(0.35f, 0.35f, 0.35f, 1);
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
	drawGrid(10, 1, 1, -45);

	/* Draw all models in the scene */
	drawMesh(-45);

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void Draw::drawSceneTop() {
	glClearColor(0.1f, 0.4f, 0.4f, 1);
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float zoom = userCameraTop->getZoom();
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(0, 1, 1, 0);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	/*  Apply camera rotations */
    glRotatef (90, 1.0f, 0.0f, 0.0f);

	/* Apply camera transforms */
	vector3D userPos = userCameraTop->getCameraPos();
	glTranslatef(userPos.x, userPos.y, userPos.z);


	/* Draw Floor */
	drawGrid(10, 1, 1, zoom);

	/* Draw all models in the scene */
	drawMesh(zoom);

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void Draw::drawSceneSide() {
	glClearColor(0.1f, 0.4f, 0.4f, 1);
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float zoom = userCameraTop->getZoom();
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(0, 1, 1, 0);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	/*  Apply camera rotations */
    glRotatef (90, 0.0f, 1.0f, 0.0f);
    glRotatef (180, 1.0f, 0.0f, 0.0f);

	/* Apply camera transforms */
	vector3D userPos = userCameraTop->getCameraPos();
	glTranslatef(userPos.x, userPos.y, userPos.z);

	/* Draw Floor */
	drawGrid(10, 1, 4, zoom);

	/* Draw all models in the scene */
	drawMesh(zoom);

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void Draw::drawSceneFront() {
	glClearColor(0.1f, 0.4f, 0.4f, 1);
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float zoom = userCameraTop->getZoom();
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(0, 1, 1, 0);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	/*  Apply camera rotations */
    glRotatef (180, 0.0f, 0.0f, 1.0f);
    glRotatef (180, 0.0f, 1.0f, 0.0f);

	/* Apply camera transforms */
	vector3D userPos = userCameraTop->getCameraPos();
	glTranslatef(userPos.x, userPos.y, userPos.z);

	/* Draw Floor */
	drawGrid(10, 1, 2, zoom);

	/* Draw all models in the scene */
	drawMesh(zoom);

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void Draw::drawGrid(int gridLines, int gridSpacing, int xyzFLAG, float zoom) {
	int	colorY = 0;
	int	colorX = 0;
	int	colorZ = 0;
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	if (xyzFLAG & 1) {
		/* XZ */
		colorZ = 1;
		colorX = 1;

		for (int i = -gridLines; i <= gridLines; i++) {
			/* X lines */
			if (i != 0) {	
				glVertex3f(i / (10.0 + (zoom * 0.2)), 0.0f, -gridLines / (10.0 + (zoom * 0.2)));
				glVertex3f(i / (10.0 + (zoom * 0.2)), 0.0f, gridLines / (10.0 + (zoom * 0.2)));

				/* Z lines */
				glVertex3f(-gridLines / (10.0 + (zoom * 0.2)), 0.0f, gridSpacing * i / (10.0 + (zoom * 0.2)));
				glVertex3f(gridLines / (10.0 + (zoom * 0.2)), 0.0f, gridSpacing * i / (10.0 + (zoom * 0.2)));
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
				glVertex3f(i / (10.0 + (zoom * 0.2)), -gridLines / (10.0 + (zoom * 0.2)), 0.0f);
				glVertex3f(i / (10.0 + (zoom * 0.2)), gridLines / (10.0 + (zoom * 0.2)), 0.0f);

				/* X lines */
				glVertex3f(-gridLines / (10.0 + (zoom * 0.2)), gridSpacing * i / (10.0 + (zoom * 0.2)), 0.0f);
				glVertex3f(gridLines / (10.0 + (zoom * 0.2)), gridSpacing * i / (10.0 + (zoom * 0.2)), 0.0f);
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
				glVertex3f(0.0f, i / (10.0 + (zoom * 0.2)), -gridLines / (10.0 + (zoom * 0.2)));
				glVertex3f(0.0f, i / (10.0 + (zoom * 0.2)), gridLines / (10.0 + (zoom * 0.2)));

				/* Z lines */
				glVertex3f(0.0f, -gridLines / (10.0 + (zoom * 0.2)), gridSpacing * i / (10.0 + (zoom * 0.2)));
				glVertex3f(0.0f, gridLines / (10.0 + (zoom * 0.2)), gridSpacing * i / (10.0 + (zoom * 0.2)));
			}
		}
	}

	/* X */
	if (colorX) {
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-gridLines / (10.0 + (zoom * 0.2)), 0.0f, 0.0f);
		glVertex3f(gridLines / (10.0 + (zoom * 0.2)), 0.0f, 0.0f);
	}

	/* Y */
	if (colorY) {
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -gridLines / (10.0 + (zoom * 0.2)), 0.0f);
		glVertex3f(0.0f, gridLines / (10.0 + (zoom * 0.2)), 0.0f);
	}

	/* Z */
	if (colorZ) {
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -gridLines / (10.0 + (zoom * 0.2)));
		glVertex3f(0.0f, 0.0f, gridLines / (10.0 + (zoom * 0.2)));
	}
	glEnd();
}

void Draw::drawCube() {
	int transpose = 3.0f;
	glBegin(GL_QUADS);
	glColor3f(0.6f, 0.1f, 0.3f);

	/* bottom */
	glVertex3f(1.0f, -1.0f, 1.0f + transpose);
	glVertex3f(1.0f, -1.0f, -1.0f + transpose);
	glVertex3f(-1.0f, -1.0f, -1.0f + transpose);
	glVertex3f(-1.0f, -1.0f, 1.0f + transpose);
	/* top */
	glVertex3f(1.0f, 1.0f, 1.0f + transpose);
	glVertex3f(1.0f, 1.0f, -1.0f + transpose);
	glVertex3f(-1.0f, 1.0f, -1.0f + transpose);
	glVertex3f(-1.0f, 1.0f, 1.0f + transpose);

	/* left */
	glVertex3f(-1.0f, 1.0f, -1.0f + transpose);
	glVertex3f(-1.0f, -1.0f, -1.0f + transpose);
	glVertex3f(-1.0f, -1.0f, 1.0f + transpose);
	glVertex3f(-1.0f, 1.0f, 1.0f + transpose);
	/* right */
	glVertex3f(1.0f, 1.0f, -1.0f + transpose);
	glVertex3f(1.0f, -1.0f, -1.0f + transpose);
	glVertex3f(1.0f, -1.0f, 1.0f + transpose);
	glVertex3f(1.0f, 1.0f, 1.0f + transpose);

	/* front */
	glVertex3f(1.0f, 1.0f, -1.0f + transpose);
	glVertex3f(1.0f, -1.0f, -1.0f + transpose);
	glVertex3f(-1.0f, -1.0f, -1.0f + transpose);
	glVertex3f(-1.0f, 1.0f, -1.0f + transpose);
	/* back */
	glVertex3f(1.0f, 1.0f, 1.0f + transpose);
	glVertex3f(1.0f, -1.0f, 1.0f + transpose);
	glVertex3f(-1.0f, -1.0f, 1.0f + transpose);
	glVertex3f(-1.0f, 1.0f, 1.0f + transpose);
	glEnd();
}

void Draw::drawMesh(float zoom) {
	std::vector<vector3D> vertexArray = mesh->getVertices();
	/* Draw all the mesh's quads */
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	std::vector<FaceData> quadArray = mesh->getQuads();
	for (unsigned int i = 0; i < quadArray.size(); i++) {
		int quadSize = quadArray.at(0).vertexPoint.size();
		for (int j = 0; j < quadSize; ++j) {
			glVertex3f(vertexArray.at(quadArray.at(i).vertexPoint.at(j) - 1).x / (10.0 + (zoom * 0.2)), 
					   vertexArray.at(quadArray.at(i).vertexPoint.at(j) - 1).y / (10.0 + (zoom * 0.2)), 
					   vertexArray.at(quadArray.at(i).vertexPoint.at(j) - 1).z / (10.0 + (zoom * 0.2)));
		}
	}
	glEnd();

	/* Draw all the mesh's triangles */
	std::vector<FaceData> triArray = mesh->getTris();
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < triArray.size(); i++) {
		int triSize = triArray.at(0).vertexPoint.size();
		for (int j = 0; j < triSize; ++j) {
			glVertex3f(vertexArray.at(triArray.at(i).vertexPoint.at(j) - 1).x / (10 + (zoom * 0.2)), 
					   vertexArray.at(triArray.at(i).vertexPoint.at(j) - 1).y / (10 + (zoom * 0.2)), 
					   vertexArray.at(triArray.at(i).vertexPoint.at(j) - 1).z / (10 + (zoom * 0.2)));
		}
	}
	glEnd();
	vertexArray.clear();
	quadArray.clear();
	triArray.clear();
}
