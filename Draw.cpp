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
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.4f, 0.6f);
	glVertex3f(5.0f, 0.0f, 5.0f);
	glVertex3f(5.0f, 0.0f, -5.0f);
	glVertex3f(-5.0f, 0.0f, -5.0f);
	glVertex3f(-5.0f, 0.0f, 5.0f);
	glEnd();

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
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.4f, 0.6f);
	glVertex3f(5.0f, 0.0f, 5.0f);
	glVertex3f(5.0f, 0.0f, -5.0f);
	glVertex3f(-5.0f, 0.0f, -5.0f);
	glVertex3f(-5.0f, 0.0f, 5.0f);
	glEnd();

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