/*
 * Obj.h
 *
 *  Created on: 20 Jan 2019
 *      Author: Samuel
 */

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <regex>

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

// Other files
#include <source/Shapes/Shape.h>

// Other .hpp
#include "common/shader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/controls.hpp"

#ifndef SOURCE_SHAPES_OBJ_H_
#define SOURCE_SHAPES_OBJ_H_

class Obj : public Shape {
public:
	Obj(std::string, float, float, float);
	virtual ~Obj();

private:
	GLfloat* getObjectVertices(std::string, std::regex);
	GLuint* getObjectFaces(std::string, std::regex);
};

#endif /* SOURCE_SHAPES_OBJ_H_ */
