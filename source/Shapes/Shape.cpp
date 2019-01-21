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
	colourBuffer = 0;
	normalBuffer = 0;
	vertexCount = 0;
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

void Shape::setColourbuffer(GLuint colourbuffer_){
	colourBuffer = colourbuffer_;
}

void Shape::setNormalbuffer(GLuint normalbuffer_){
	normalBuffer = normalbuffer_;
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

int Shape::getVertexCount(){
	return vertexCount;
}

GLuint Shape::getVertexbuffer(){
	return vertexBuffer;
}

GLuint* Shape::getVertexbufferAddress(){
	return &vertexBuffer;
}

GLuint Shape::getColourbuffer(){
	return colourBuffer;
}

GLuint* Shape::getColourbufferAddress(){
	return &colourBuffer;
}

GLuint Shape::getNormalbuffer(){
	return normalBuffer;
}

GLuint* Shape::getNormalbufferAddress(){
	return &normalBuffer;
}
