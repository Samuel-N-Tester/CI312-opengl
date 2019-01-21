/*
 * Viewer.h
 *
 *  Created on: 12 Oct 2018
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

// Other files
#include <source/Main/Model.h>

// Other .hpp
#include "common/shader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/controls.hpp"

using namespace glm;

#ifndef SOURCE_EXAMPLE1_VIEWER_H_
#define SOURCE_EXAMPLE1_VIEWER_H_

class Viewer {
public:
	Viewer(std::shared_ptr<Model>);
	virtual ~Viewer();
	void init();
	bool render();

private:
	void addViewport();
	void drawShape(GLuint*, GLuint*, GLuint*, int);

	std::shared_ptr<Model> model;
	int width;
	int height;
};

#endif /* SOURCE_EXAMPLE1_VIEWER_H_ */
