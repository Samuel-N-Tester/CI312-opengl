/*
 * Viewer.cpp
 *
 *  Created on: 12 Oct 2018
 *      Author: Samuel
 */
#include <source/Main/Viewer.h>

GLFWwindow* window;
GLuint programID;
GLuint VertexArrayID;

GLuint MatrixID;
GLuint ViewID;
GLuint ModelID;
GLuint LightID;
GLuint CameraID;

Viewer::Viewer(std::shared_ptr<Model> model_) {
	model = model_;
	width = 1000;
	height = 500;
}

Viewer::~Viewer() {
	// Cleanup VBO and shader
	// glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void Viewer::init() {

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return void();
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "Basic Example", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr,
				"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return void();
	}
	glfwMakeContextCurrent(window);


	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// Hide the mouse and enable unlimited mouvement
	glfwPollEvents();
	glfwSetCursorPos(window, width / 2, height / 2);// Set the mouse at the center of the screen
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);// Dark blue background

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return void();
	}

	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	// glEnable(GL_CULL_FACE);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl", "LightFragmentShader.hlsl", "LightVertexShader.hlsl");
	programID = LoadShaders("LightFragmentShader.hlsl", "LightVertexShader.hlsl");
}

bool Viewer::render() {

	bool running = true;

	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glUseProgram(programID);
	computeMatricesFromInputs(window, width, height);


	//********Calculate the MVP matrix

	glm::mat4 Projection;
	Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);


	// Camera matrix

	glm::mat4 View = glm::lookAt(
			glm::vec3(0, 0, 2), // Camera is at (0,0,-1), in World Space
			glm::vec3(0.0, 0.0, 0.0), // and looks at the origin
			glm::vec3(0.0, 1.0, 0.0)  // Head is up (set to 0,-1,0 to look upside-down)
	);


	// Model matrix

	glm::mat4 Model = glm::mat4(1.0);

	// Our ModelViewProjection : multiplication of our 3 matrices

	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewID = glGetUniformLocation(programID, "V");
    ModelID = glGetUniformLocation(programID, "M");
    LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
    CameraID = glGetUniformLocation(programID, "CameraPosition_worldspace");

    glm::mat4 mvp = Projection * View * Model;

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(ModelID, 1, GL_FALSE, &View[0][0]);
    glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);

    glm::vec3 lightPosition = glm::vec3(10, 10, 0); // Lights up at
    glm::vec3 cameraPosition = glm::vec3(0, 0, 0); // Looks at the origin

    glUniform3f(LightID, lightPosition.x, lightPosition.y, lightPosition.z);
    glUniform3f(CameraID, cameraPosition.x, cameraPosition.y, cameraPosition.z);



	 // Remember, matrix multiplication is the other way around

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    std::vector<Shape*> shapes = model->getShapes();
    for (std::vector<Shape*>::iterator it = shapes.begin() ; it != shapes.end(); ++it){
        Shape* myshape = *it;
        drawShape(myshape->getVertexbufferAddress(), myshape->getColourbufferAddress(), myshape->getNormalbufferAddress(), myshape->getVertexCount());
    }

	// Swap buffers

	glfwSwapBuffers(window);
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window) != 0) {
		running = false;
	}

	return running;
}

void Viewer::drawShape(GLuint *vertexbuffer, GLuint *colorbuffer, GLuint *normalbuffer, int vertexCount){
	//********Add the Geometry
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
	glVertexAttribPointer(
			0,			// attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,			// size
			GL_FLOAT,	// type
			GL_FALSE,	// normalized?
			0,			// stride
			(void*) 0	// array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, *colorbuffer);
	glVertexAttribPointer(
			1,			// attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,			// size
			GL_FLOAT,	// type
			GL_FALSE,	// normalized?
			0,			// stride
			(void*) 0	// array buffer offset
	);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, *normalbuffer);
    glVertexAttribPointer(
    		2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0,vertexCount); // 3 indices starting at 0 -> 1

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
