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
#include "utils.h"

struct FaceData {
  std::vector<int> vertexPoint;
  std::vector<int> vertexTexture;
  std::vector<int> vertexNormal;
};

class Model {

public:
  Model(std::string fileName); 
  ~Model();

  std::string meshName;
  std::vector<vector3D> vertexArray;
  std::vector<FaceData> quadArray;
  std::vector<FaceData> triArray;

  void myPrint();
  std::vector<vector3D> getVertices();
  std::vector<FaceData> getQuads();
  std::vector<FaceData> getTris();

private:
  void parseMesh(std::string fileName);
  std::string parseName(std::string line);
  vector3D parseVertex(std::string line);
  FaceData parseFace(std::vector<std::string> elements);
  std::vector<std::string> split(const std::string &s, char delim);
};
#endif
