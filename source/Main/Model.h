/*
 * Model.h
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

// Other files
#include <source/Shapes/Shape.h>
#include <source/Shapes/Tetrahedron.h>

// Other .hpp
#include "common/shader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/controls.hpp"

using namespace glm;

#ifndef SOURCE_MAIN_MODEL_H_
#define SOURCE_MAIN_MODEL_H_

class Model {
public:
	Model();
	virtual ~Model();
	void addShape(std::shared_ptr<Shape>);

	std::shared_ptr<std::vector<std::shared_ptr<Shape>>> getShapes();

	void setShapes(std::shared_ptr<std::vector<std::shared_ptr<Shape>>>);

private:
	std::vector<std::shared_ptr<Shape>> shapes;
};

#endif /* SOURCE_MAIN_MODEL_H_ */
