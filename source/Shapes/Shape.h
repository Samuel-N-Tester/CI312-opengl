/*
 * Shape.h
 *
 *  Created on: 5 Nov 2018
 *      Author: Samuel
 */

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>

// Include GLEW
#include <GL/glew.h>
#include <glfw3.h>

// Include GLM
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// Other .hpp
#include "common/shader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/controls.hpp"

using namespace glm;

#ifndef SOURCE_MAIN_SHAPE_H_
#define SOURCE_MAIN_SHAPE_H_

class Shape {
public:
	Shape();
	virtual ~Shape();

	void setX(float);
	void setY(float);
	void setZ(float);
	void setVertexbuffer(GLuint);
	void setColourbuffer(GLuint);
	void setnormalbuffer(GLuint);
	void setNormalbuffer(GLuint);

	float getX();
	float getY();
	float getZ();
	int getVertexCount();
	GLuint getVertexbuffer();
	GLuint getColourbuffer();
	GLuint getnormalbuffer();
	GLuint getNormalbuffer();
	GLuint* getVertexbufferAddress();
	GLuint* getColourbufferAddress();
	GLuint* getnormalbufferAddress();
	GLuint* getNormalbufferAddress();

protected:
	void setPosition(float, float, float);

	float xPos;
	float yPos;
	float zPos;
	int vertexCount;
	GLuint vertexBuffer;
	GLuint colourBuffer;
	GLuint normalBuffer;
};

#endif /* SOURCE_MAIN_SHAPE_H_ */
