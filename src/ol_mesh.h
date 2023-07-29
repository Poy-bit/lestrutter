#pragma once

#include <iostream>

#include "glad/glad.h"
#include "tiny_gltf.h"

// An outline mesh is a mesh with two materials, one of which being an outline material colored the same as the background
class ol_mesh {
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;

	int indices_count;

	void lbuf_indices(tinygltf::Model model, int mat_prim, int out_prim, int vert_count);

public:
	int mvc;

	ol_mesh(tinygltf::Model model, int node_index);
	void draw();
};