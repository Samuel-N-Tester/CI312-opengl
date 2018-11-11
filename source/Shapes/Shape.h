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
	void setColorbuffer(GLuint);
	void setElementbuffer(GLuint);

	float getX();
	float getY();
	float getZ();
	GLuint getVertexbuffer();
	GLuint getColourbuffer();
	GLuint getElementbuffer();
	GLuint* getVertexbufferAddress();
	GLuint* getColourbufferAddress();
	GLuint* getElementbufferAddress();

protected:
	void setPosition(float, float, float);

	float xPos;
	float yPos;
	float zPos;
	GLuint vertexBuffer;
	GLuint elementBuffer;
	GLuint colorBuffer;
	int elementCount;
};

#endif /* SOURCE_MAIN_SHAPE_H_ */
