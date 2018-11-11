/*
 * Tetrahedron.h
 *
 *  Created on: 5 Nov 2018
 *      Author: Samuel
 */

/*
 * Model.h
 *
 *  Created on: 5 Nov 2018
 *      Author: Samuel
 */

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

// Other .hpp
#include "common/shader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/controls.hpp"

#ifndef SOURCE_MAIN_TETRAHEDRON_H_
#define SOURCE_MAIN_TETRAHEDRON_H_

class Tetrahedron : public Shape {
public:
	Tetrahedron(float, float, float, float);
	virtual ~Tetrahedron();
	void buildTetrahedron();

	void setSize(int);
	int getSize();

private:
	int size;
};

#endif /* SOURCE_MAIN_TETRAHEDRON_H_ */
