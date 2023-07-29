#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION

#include <iostream>
#include <SDL.h>
#include "glad/glad.h"

#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include "shader.h"
#include "camera.h"
#include "ol_mesh.h"

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
	glEnable(GL_DEPTH_TEST);

	// Load parts model from file
	std::string filename = SOURCE_PATH + std::string("/res/parts.glb");
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	bool res = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
	if (!warn.empty()) {
		std::cout << "Loader Warning: " << warn << std::endl;
	}

	if (!err.empty()) {
		std::cout << "Loader Error: " << err << std::endl;
	}

	if (!res)
		std::cout << "Failed to load glTF: " << filename << std::endl;

	tinygltf::Scene scene = model.scenes[model.defaultScene];
	tinygltf::Node armature = model.nodes[scene.nodes[0]];
	ol_mesh parts = ol_mesh(model, armature.children[0]);

	shader mainShader = shader(SOURCE_PATH+std::string("/res/shaders/vert.txt"), SOURCE_PATH+std::string("/res/shaders/frag.txt"));
	mainShader.bind();

	camera theCamera;

	glClearColor(105/255.0, 81/255.0, 88/255.0, 1.0);

	mainShader.setVec3("material_color[0]", 105/255.0, 81/255.0, 88/255.0);
	mainShader.setVec3("material_color[1]", 40/255.0, 44/255.0, 52/255.0);

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case (SDL_QUIT): { quit = true; break; }
			case (SDL_MOUSEBUTTONDOWN): {
				theCamera.mousedown_ev(e.button); break;
			} case (SDL_MOUSEBUTTONUP): {
				theCamera.mouseup_ev(e.button); break;
			} case (SDL_MOUSEMOTION): {
				theCamera.mousemove_ev(e.motion); break;
			} case (SDL_MOUSEWHEEL): {
				theCamera.mousewheel_ev(e.wheel); break; 
			}
			}
		}

		mainShader.setMat4("cammat", theCamera.gen_mat());
		mainShader.setMat4("projection", theCamera.projection());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		parts.draw();

		SDL_GL_SwapWindow(window);
	}

	return 0;
}
