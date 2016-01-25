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
using namespace std;

struct vector3D {
  float x;
  float y;
  float z;
};

struct FaceData {
  int vertexPoint;
  int vertexTexture;
  int vertexNormal;
};

class Model {
  
  public:
    // string name here

public:
  Model(string fileName); 
  ~Model();
  
  string meshName;
  vector<vector3D> vertexArray;
  vector<FaceData> faceArray;

  void myPrint();
  vector<vector3D> getVertices();
  vector<FaceData> getFaces();

private:
  void parseMesh(string fileName);
  string parseName(string line);
  vector3D parseVertex(string line);
  FaceData parseFace(string line);
  vector<string> split(const string &s, char delim);
};
#endif
