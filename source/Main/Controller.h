/*
 * Controller.h
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
#include <source/Main/Model.h>
#include <source/Main/Viewer.h>
#include <source/Shapes/Tetrahedron.h>
#include <source/Shapes/Obj.h>

// Other .hpp
#include "common/shader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/controls.hpp"

#ifndef SOURCE_MAIN_CONTROLLER_H_
#define SOURCE_MAIN_CONTROLLER_H_

class Controller {
public:
	Controller(std::shared_ptr<Model>, std::shared_ptr<Viewer>);
	virtual ~Controller();
	void run();
	void init();
	void loop();

private:
	std::shared_ptr<Model> model;
	std::shared_ptr<Viewer> view;
	bool running;
};

#endif /* SOURCE_MAIN_CONTROLLER_H_ */
