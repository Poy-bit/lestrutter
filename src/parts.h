#pragma once

#include <iostream>

#include "glad/glad.h"
#include "tiny_gltf.h"

class parts {
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;

	int indices_count;

public:
	parts();
	void draw();
};