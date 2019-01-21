/*
 * Obj.cpp
 *
 *  Created on: 20 Jan 2019
 *      Author: Samuel
 */

#include <source/Shapes/Obj.h>

Obj::Obj(std::string type, float x, float y, float z) {

	xPos = x;
	yPos = y;
	zPos = z;

    std::vector<unsigned short> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    bool res = loadAssImp("C:\\cppObjects\\ball.obj", indices, vertices, uvs, normals);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    std::vector<glm::vec3> colors;

    int colour = 0;
    for (int i = 0; i < vertices.size(); i++) {
    	switch(colour){
			case 0:
				colors.push_back(glm::vec3(1.0, 0.0, 0.0));
				colour++;
				break;
			case 1:
				colors.push_back(glm::vec3(0.0, 1.0, 0.0));
				colour++;
				break;
			case 2:
				colors.push_back(glm::vec3(0.0, 0.0, 1.0));
				colour = 0;
				break;
			default:
			std::cout << "Something went wrong" << std::endl;
    	}
    }

    glGenBuffers(1, &colourBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);

    vertexCount = indices.size()*3;
}

Obj::~Obj() {
	// TODO Auto-generated destructor stub
}
