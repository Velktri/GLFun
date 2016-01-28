#include "Model.h"

Model::Model(string fileName) {
  parseMesh(fileName);
}

Model::~Model() {

}

void Model::parseMesh(string fileName) {
  string line;
  ifstream myFile(fileName.c_str());
  if (myFile.is_open()) {
    while (getline(myFile, line)) {
      if (line.at(0) == 'o') {
        meshName = parseName(line);
      } else if (line.at(0) == 'v' && line.at(1) == ' ') {
        vertexArray.push_back(parseVertex(line));
      } else if (line.at(0) == 'f') {
        vector<string> elements = split(line, ' ');
        if ((elements.size() - 1) == 4) {
          quadArray.push_back(parseFace(elements));
        } else if ((elements.size() - 1) == 3) {
          triArray.push_back(parseFace(elements));
        }
        elements.clear();
      } else {
        // N-Gons
      }
    }
  }
  myFile.close();
}

void Model::myPrint() {
  cout << meshName << endl;
}

vector<vector3D> Model::getVertices() {
  return vertexArray;
}

vector<FaceData> Model::getQuads() {
  return quadArray;
}

vector<FaceData> Model::getTris() {
  return triArray;
}

string Model::parseName(string line) {
  string name;
  vector<string> elements = split(line, ' ');
  name = elements.at(1);
  elements.clear();

  return name;
}

vector3D Model::parseVertex(string line) {
  vector3D point;
  vector<string> elements = split(line, ' ');
  point.x = atof(elements[1].c_str());
  point.y = atof(elements[2].c_str());
  point.z = atof(elements[3].c_str());
  elements.clear();

  return point;
}

FaceData Model::parseFace(vector<string> elements) {
  FaceData quad;
  vector<string> subElement;
  for (unsigned int i = 1; i < elements.size(); ++i)
  {
    subElement = split(elements[i], '/');
    quad.vertexPoint.push_back(atoi(subElement[0].c_str()));
    quad.vertexTexture.push_back(atoi(subElement[1].c_str()));
    quad.vertexNormal.push_back(atoi(subElement[2].c_str()));
  }
  subElement.clear();

  return quad;
}

vector<string> Model::split(const string &s, char delim) {
  vector<string> elements;
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elements.push_back(item);
  }
  return elements;
}
