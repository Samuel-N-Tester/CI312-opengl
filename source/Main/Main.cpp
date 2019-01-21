// Include other files
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>

// Include GLEW
#include <GL/glew.h>
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// Include all .h files
#include <source/Main/Controller.h>
#include <source/Main/Model.h>
#include <source/Main/Viewer.h>

//Include hpp files
#include "common/shader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/controls.hpp"

using namespace glm;

int main(void){

	std::shared_ptr<Model> model(new Model());
	std::shared_ptr<Viewer> view(new Viewer(model));
	std::shared_ptr<Controller> controller(new Controller(model, view));

    controller->run();

	controller->~Controller();
	view->~Viewer();
	model->~Model();

    return 0;
}
