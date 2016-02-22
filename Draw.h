/*  Geoffrey Murray
 *  This class controls all
 *  scene drawing for the
 *	windows.
 */

#ifndef DRAW_H
#define DRAW_H
#include <stdlib.h>
#include <vector>
#include "utils.h"
#include "Camera.h"
#include "Model.h"

 /* GLUT */
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class Draw {
private:
	Camera* userCamera;
	Model* mesh;

public:
	Draw(Camera* userCamera, Model* mod);
	~Draw();

	/* Draws the floor grid */
	void drawGrid(int gridLines, int gridSpacing, int xyzFLAG);

	/* Draws the full window */
	void drawApplication();

	/* Draws the 3D scene sub window */
	void drawScene();

	/* Draws the top view window */
	void drawSceneTop();
};
#endif