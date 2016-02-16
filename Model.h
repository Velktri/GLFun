/* Geoffrey Murray
 * 1/12/2016
 * This class will hold all of
 * the mesh information.
 */

#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <iostream>
#include "utils.h"
using namespace std;

struct FaceData {
  vector<int> vertexPoint;
  vector<int> vertexTexture;
  vector<int> vertexNormal;
};

class Model {

public:
  Model(string fileName); 
  ~Model();

  string meshName;
  vector<vector3D> vertexArray;
  vector<FaceData> quadArray;
  vector<FaceData> triArray;

  void myPrint();
  vector<vector3D> getVertices();
  vector<FaceData> getQuads();
  vector<FaceData> getTris();

private:
  void parseMesh(string fileName);
  string parseName(string line);
  vector3D parseVertex(string line);
  FaceData parseFace(vector<string> elements);
  vector<string> split(const string &s, char delim);
};
#endif
