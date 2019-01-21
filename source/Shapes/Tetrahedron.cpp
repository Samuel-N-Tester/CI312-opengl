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
	float triangleHeight;		// Height of each triangle pane
	float tetrahedronHeight;	// Height of the tetrahedron

	float temp;
	temp = sizeSq + pow(size/2, 2);
	triangleHeight = sqrt(temp);

	temp = sizeSq + pow(triangleHeight, 2);
	tetrahedronHeight = sqrt(temp);

	//Build the vertices

	GLfloat g_vertex_buffer_data[] = {
	        xPos, yPos+(tetrahedronHeight/2), zPos,								// Top
			xPos, yPos-(tetrahedronHeight/2), zPos+(triangleHeight/2),			// Middle
			xPos-(size/2), yPos-(tetrahedronHeight/2), zPos-(triangleHeight/2),	// Left

	        xPos, yPos+(tetrahedronHeight/2), zPos,								// Top
			xPos, yPos-(tetrahedronHeight/2), zPos+(triangleHeight/2),			// Middle
			xPos+(size/2), yPos-(tetrahedronHeight/2), zPos-(triangleHeight/2),	// Right

	        xPos, yPos+(tetrahedronHeight/2), zPos,								// Top
			xPos-(size/2), yPos-(tetrahedronHeight/2), zPos-(triangleHeight/2),	// Left
			xPos+(size/2), yPos-(tetrahedronHeight/2), zPos-(triangleHeight/2),	// Right

			xPos, yPos-(tetrahedronHeight/2), zPos+(triangleHeight/2),			// Middle
			xPos-(size/2), yPos-(tetrahedronHeight/2), zPos-(triangleHeight/2),	// Left
			xPos+(size/2), yPos-(tetrahedronHeight/2), zPos-(triangleHeight/2),	// Right
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	//Colour the vertices
	GLfloat g_color_buffer_data[] = {

			//Left Face
			0.0, 1.0, 0.0f,	// Top
			0.0, 1.0, 0.0f,	// Middle
			0.0, 1.0, 0.0f,	// Left

			//Right Face
			1.0, 0.0, 0.0f,	// Top
			1.0, 0.0, 0.0f,	// Middle
			1.0, 0.0, 0.0f,	// Right

			//Back Face
			1.0, 0.0, 0.0f,	// Top
			1.0, 0.0, 0.0f,	// Left
			1.0, 0.0, 0.0f,	// Right

			//Bottom Face
			1.0, 0.0, 0.0f,	// Middle
			1.0, 0.0, 0.0f,	// Left
			1.0, 0.0, 0.0f,	// Right
	};

	glGenBuffers(1, &colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	vertexCount = 12;
}

Tetrahedron::~Tetrahedron() {
	// TODO Auto-generated destructor stub
}
