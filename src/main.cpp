#include <iostream>
#include <SDL.h>
#include "glad/glad.h"

#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include "shader.h"
#include "camera.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include "tiny_gltf.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO); // TODO: Add to tests

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window* window = SDL_CreateWindow("Lestrutter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	SDL_GLContext gl_context = SDL_GL_CreateContext(window); // TODO: Add to tests
	SDL_GL_MakeCurrent(window, gl_context);

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	SDL_GL_SetSwapInterval(1); // Important Apparently

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress); // TODO: Add to tests

	std::string filename = SOURCE_PATH + std::string("/res/parts.glb");
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	bool res = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
	if (!warn.empty()) {
		std::cout << "WARN: " << warn << std::endl;
	}

	if (!err.empty()) {
		std::cout << "ERR: " << err << std::endl;
	}

	if (!res)
		std::cout << "Failed to load glTF: " << filename << std::endl;
	else
		std::cout << "Loaded glTF: " << filename << std::endl;

	tinygltf::Scene scene = model.scenes[model.defaultScene];
	tinygltf::Node armature = model.nodes[scene.nodes[0]];
	tinygltf::Node node = model.nodes[armature.children[0]];
	tinygltf::Mesh mesh = model.meshes[node.mesh];

	tinygltf::Accessor pos_accessor = model.accessors[mesh.primitives[0].attributes["POSITION"]];
	tinygltf::BufferView pos_bufferview = model.bufferViews[pos_accessor.bufferView];
	tinygltf::Accessor index_accessor = model.accessors[mesh.primitives[0].indices];
	tinygltf::BufferView index_bufferview = model.bufferViews[index_accessor.bufferView];

	// Sanity Check
	assert(pos_accessor.componentType == GL_FLOAT);
	assert(pos_accessor.count == pos_bufferview.byteLength / sizeof(float) / pos_accessor.type);
	assert(index_accessor.componentType == GL_UNSIGNED_SHORT);
	assert(index_accessor.count == index_bufferview.byteLength / sizeof(short));

	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	void* data = (void*)&model.buffers[pos_bufferview.buffer].data[pos_bufferview.byteOffset];
	glBufferData(pos_bufferview.target, pos_bufferview.byteLength, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	data = (void*)&model.buffers[index_bufferview.buffer].data[index_bufferview.byteOffset];
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_bufferview.byteLength, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, pos_accessor.type, GL_FLOAT, GL_FALSE, pos_accessor.type * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//tinygltf::Material mat1 = model.materials[mesh.primitives[0].material];

	shader mainShader = shader(SOURCE_PATH+std::string("/res/shaders/vert.txt"), SOURCE_PATH+std::string("/res/shaders/frag.txt"));
	mainShader.bind();

	camera theCamera;

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case (SDL_QUIT): { quit = true; break; }
			case (SDL_MOUSEBUTTONDOWN): {
				theCamera.mousedown_ev(e.button); break;
			} case (SDL_MOUSEBUTTONUP): {
				theCamera.mouseup_ev(e.button);  break;
			} case (SDL_MOUSEMOTION): {
				theCamera.mousemove_ev(e.motion);  break;
			} case (SDL_MOUSEWHEEL): {
				theCamera.mousewheel_ev(e.wheel); break; 
			}
			}
		}

		mainShader.setMat4("cammat", theCamera.gen_mat());
		mainShader.setMat4("projection", theCamera.projection());

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, index_accessor.count, GL_UNSIGNED_SHORT, 0);

		SDL_GL_SwapWindow(window);
	}

	return 0;
}
