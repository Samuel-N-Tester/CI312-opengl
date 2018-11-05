// Include other files
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// Include all .h files
#include <source/Main/Viewer.h>
#include <source/Main/Model.h>

//Include hpp files
#include "common/shader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/controls.hpp"

using namespace glm;

bool running = true;

int main(void){

	Viewer viewer;
	viewer.init();

	std::shared_ptr<Model> model(new Model());

	while(running){
		running = viewer.render();
	}

	viewer.~Viewer();
    
    return 0;
}
