#include "Model.h"

Model::Model(std::string fileName) {
  parseMesh(fileName);
}

Model::~Model() {

}

void Model::parseMesh(std::string fileName) {
  std::string line;
  std::ifstream myFile(fileName.c_str());
  if (myFile.is_open()) {
    while (getline(myFile, line)) {
      if (line.at(0) == 'o') {
        meshName = parseName(line);
      } else if (line.at(0) == 'v' && line.at(1) == ' ') {
        vertexArray.push_back(parseVertex(line));
      } else if (line.at(0) == 'f') {
        std::vector<std::string> elements = split(line, ' ');
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
  std::cout << meshName << std::endl;
}

std::vector<vector3D> Model::getVertices() {
  return vertexArray;
}

std::vector<FaceData> Model::getQuads() {
  return quadArray;
}

std::vector<FaceData> Model::getTris() {
  return triArray;
}

std::string Model::parseName(std::string line) {
  std::string name;
  std::vector<std::string> elements = split(line, ' ');
  name = elements.at(1);
  elements.clear();

  return name;
}

vector3D Model::parseVertex(std::string line) {
  vector3D point;
  std::vector<std::string> elements = split(line, ' ');
  point.x = atof(elements[1].c_str());
  point.y = atof(elements[2].c_str()) + 1.0;
  point.z = atof(elements[3].c_str());
  elements.clear();

  return point;
}

FaceData Model::parseFace(std::vector<std::string> elements) {
  FaceData quad;
  std::vector<std::string> subElement;
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

std::vector<std::string> Model::split(const std::string &s, char delim) {
  std::vector<std::string> elements;
  std::stringstream ss(s);
  std::string item;
  while (getline(ss, item, delim)) {
    elements.push_back(item);
  }
  return elements;
}