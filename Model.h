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

class Model {
  
  public:
    // string name here

public:
  Model(string fileName); 
  ~Model();
  
  string meshName;
  vector<vector3D> vertexArray;
  void myPrint();
  vector<vector3D> getVertices();  

private:
  void parseMesh(string fileName);
  string parseName(string line);
  vector3D parseVertex(string line);
  vector<string> split(const string &s, char delim);
};
#endif
