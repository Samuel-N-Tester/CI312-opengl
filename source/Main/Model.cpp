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

void Model::addShape(std::shared_ptr<Shape> shape){
	shapes.push_back(shape);
}

std::shared_ptr<std::vector<std::shared_ptr<Shape>>> Model::getShapes(){
	//return //std::shared_ptr<std::vector<std::shared_ptr<Shape>>>shapes_(shapes);
	return std::make_shared<std::vector<std::shared_ptr<Shape>>>(shapes);
}
