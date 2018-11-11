/*
 * Tetrahedron.cpp
 *
 *  Created on: 5 Nov 2018
 *      Author: Samuel
 */

#include <source/Shapes/Tetrahedron.h>

Tetrahedron::Tetrahedron(float x, float y, float z, float size_) {

	xPos = x;
	yPos = y;
	zPos = z;
	size = size_;

	//Calculate the dimensions

	float sizeSq = pow(size, 2);
	float h; // Height of the tetrahedron
	float H; // Height of each triangle pane

	float temp;
	temp = sizeSq + pow(size/2, 2);
	h = sqrt(temp);

	temp = sizeSq + pow(h, 2);
	H = sqrt(temp);


	//Build the vertices

	static const GLfloat g_vertex_buffer_data[] = {
			xPos, yPos, zPos,					// Top
			xPos, yPos-H, zPos-(h/2),			// Middle
			xPos-(size/2), yPos-H, zPos+(h/2),	// Left
			xPos+(size/2), yPos-H, zPos+(h/2),	// Right
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	//Build the faces

	GLuint g_element_buffer_data []  {
			0, 1, 2,	// Left
			0, 1, 3,	// Right
			0, 2, 3,	// Back
			1, 2, 3,	// Bottom
	};

	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_element_buffer_data), g_element_buffer_data, GL_STATIC_DRAW);


	//Colour the vertices

	static const GLfloat g_color_buffer_data[] = {
			0.0, 1.0, 0.0f,	// Top
			1.0, 0.0, 0.0f,	// Middle
			1.0, 0.0, 0.0f,	// Left
			1.0, 0.0, 0.0f,	// Right
	};

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	elementCount = 12;

	std::cout << &elementBuffer << std::endl;
}

Tetrahedron::~Tetrahedron() {
	// TODO Auto-generated destructor stub
}
