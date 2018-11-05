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
GLuint vertexbuffer;
GLuint elementbuffer;
GLuint colorbuffer;
GLuint MatrixID;
int elementCount;
int width;
int height;

Viewer::Viewer() {
	width = 1000;
	height = 500;
}

Viewer::~Viewer() {
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
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

	buildTetrahedron(0, 0, 0, 1);

	programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl");
}

void Viewer::buildTetrahedron (float x, float y, float z, float size){

	//Calculate the dimensions

	float sizeSq = pow(size, 2);
	float h; //Height of the tetrahedron
	float H; //Height of each triangle pane

	float temp;
	temp = sizeSq + pow(size/2, 2);
	h = sqrt(temp);

	temp = sizeSq + pow(h, 2);
	H = sqrt(temp);


	//Build the vertices

	static const GLfloat g_vertex_buffer_data[] = {
			x, y, z,				 //Top
			x, y-H, z-(h/2),		 //Middle
			x-(size/2), y-H, z+(h/2),//Left
			x+(size/2), y-H, z+(h/2),//Right
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	//Build the faces

	GLuint g_element_buffer_data []  {
			0, 1, 2,//Left
			0, 1, 3,//Right
			0, 2, 3,//Back
			1, 2, 3,//Bottom
	};

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_element_buffer_data), g_element_buffer_data, GL_STATIC_DRAW);


	//Colour the vertices

	static const GLfloat g_color_buffer_data[] = {
			0.0, 1.0, 0.0f,//Top
			1.0, 0.0, 0.0f,//Middle
			1.0, 0.0, 0.0f,//Left
			1.0, 0.0, 0.0f,//Right
	};

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	elementCount = 12;
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
			glm::vec3(5.0, -7.0, 5.0), // Camera is at (0,0,-1), in World Space
			glm::vec3(0.0, 0.0, 0.0), // and looks at the origin
			glm::vec3(0.0, 1.0, 0.0)  // Head is up (set to 0,-1,0 to look upside-down)
	);


	// Model matrix

	glm::mat4 Model = glm::mat4(1.0);

	// Our ModelViewProjection : multiplication of our 3 matrices

	MatrixID = glGetUniformLocation(programID, "MVP");
	glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	glViewport(0, 0, width/2, height);
	addViewport();

	glViewport(width/2, 0, width/2, height);
	addViewport();


	// Swap buffers

	glfwSwapBuffers(window);
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window) != 0) {
		running = false;
	}

	return running;
}

void Viewer::addViewport() {
	//********Add the Geometry
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
			1,			// attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,			// size
			GL_FLOAT,	// type
			GL_FALSE,	// normalized?
			0,			// stride
			(void*) 0	// array buffer offset
			);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElements(GL_TRIANGLES,
            elementCount,
            GL_UNSIGNED_INT,
            (GLvoid*) 0
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}