/*
 * Shape.cpp
 *
 *  Created on: 5 Nov 2018
 *      Author: Samuel
 */

#include <source/Shapes/Shape.h>

Shape::Shape() {
	xPos = 0.0;
	yPos = 0.0;
	zPos = 0.0;
	vertexBuffer = 0;
	elementBuffer = 0;
	colorBuffer = 0;
	elementCount = 0;
}

Shape::~Shape() {
	// TODO Auto-generated destructor stub
}

// Setters
void Shape::setPosition(float xPos_, float yPos_, float zPos_) {
	xPos = xPos_;
	yPos = yPos_;
	zPos = zPos_;
}

void Shape::setX(float xPos_){
	xPos = xPos_;
}

void Shape::setY(float yPos_){
	yPos = yPos_;
}

void Shape::setZ(float zPos_){
	zPos = zPos_;
}

void Shape::setVertexbuffer(GLuint vertexbuffer_){
	vertexBuffer = vertexbuffer_;
}

void Shape::setColorbuffer(GLuint elementbuffer_){
	elementBuffer = elementbuffer_;
}

void Shape::setElementbuffer(GLuint colorbuffer_){
	colorBuffer = colorbuffer_;
}


// Getters
float Shape::getX(){
	return xPos;
}

float Shape::getY(){
	return yPos;
}

float Shape::getZ(){
	return zPos;
}

GLuint Shape::getVertexbuffer(){
	return vertexBuffer;
}

GLuint Shape::getColourbuffer(){
	return elementBuffer;
}

GLuint Shape::getElementbuffer(){
	return colorBuffer;
}

GLuint* Shape::getVertexbufferAddress(){
	return &vertexBuffer;
}

GLuint* Shape::getColourbufferAddress(){
	return &elementBuffer;
}

GLuint* Shape::getElementbufferAddress(){
	return &colorBuffer;
}
