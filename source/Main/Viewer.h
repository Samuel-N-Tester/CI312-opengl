/*
 * Viewer.h
 *
 *  Created on: 12 Oct 2018
 *      Author: Samuel
 */

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
#include <vector>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "common/shader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/controls.hpp"
#include <glm/gtx/transform.hpp>

#ifndef SOURCE_EXAMPLE1_VIEWER_H_
#define SOURCE_EXAMPLE1_VIEWER_H_

class Viewer {
public:
	Viewer();
	virtual ~Viewer();
	void init();
	bool render();
	void buildTetrahedron(float, float, float, float);
private:
	void addViewport();
	void buildShape();
};

#endif /* SOURCE_EXAMPLE1_VIEWER_H_ */
