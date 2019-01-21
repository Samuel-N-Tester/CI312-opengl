/*
 * Model.cpp
 *
 *  Created on: 5 Nov 2018
 *      Author: Samuel
 */

#include <source/Main/Model.h>

Model::Model() {
	// TODO Auto-generated constructor stub

}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

void Model::addShape(Shape* shape){
	shapes.push_back(shape);
}

std::vector<Shape*> Model::getShapes(){
	return shapes;
}
