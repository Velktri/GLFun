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
      } else if (line.at(0) == 'v') {
        vertexArray.push_back(parseVertex(line));     
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
  point.x = atof(elements[1].c_str()) / 5;
  point.y = atof(elements[2].c_str()) / 5;   
  point.z = (atof(elements[3].c_str()) / 5) - 3.0; 
  elements.clear();  

  return point;
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
