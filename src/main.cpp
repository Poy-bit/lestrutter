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
#include "rigidbody.h"
#include "physics.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO); // TODO: Add to tests

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	SDL_Window* window = SDL_CreateWindow("Lestrutter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	SDL_GLContext gl_context = SDL_GL_CreateContext(window); // TODO: Add to tests
	SDL_GL_MakeCurrent(window, gl_context);

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	SDL_GL_SetSwapInterval(1); // Important Apparently

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress); // TODO: Add to tests
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

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

	int ball_index = -1;
	for (int i = 0; i < model.nodes.size(); i++) {
		if (model.nodes[i].name == "ball") {
			ball_index = i;
			break;
		}
	}

	ol_mesh ball = ol_mesh(model, ball_index);
	Physics world = Physics();
	Rigidbody rigidbody1 = Rigidbody(vec2(0, 2), vec2(0, -4));
	Rigidbody rigidbody2 = Rigidbody(vec2(0, -2), vec2(0, 0));
	CircleCollider collider1 = CircleCollider(&rigidbody1.pos);
	CircleCollider collider2 = CircleCollider(&rigidbody2.pos);
	
	rigidbody1.bounciness = 0;
	rigidbody2.mass = 100;

	rigidbody1.setCollider(&collider1);
	rigidbody2.setCollider(&collider2);
	world.add_body(&rigidbody1);
	world.add_body(&rigidbody2);

	shader mainShader = shader(SOURCE_PATH+std::string("/res/shaders/vert.txt"), SOURCE_PATH+std::string("/res/shaders/frag.txt"));
	mainShader.bind();

	camera theCamera;

	glClearColor(47 / 255.0, 53 / 255.0, 59 / 255.0, 1.0);

	mainShader.setVec3("material_color[0]", 47 / 255.0, 53 / 255.0, 59 / 255.0);
	mainShader.setVec3("material_color[1]", 62/255.0, 146/255.0, 204/255.0);

	Uint64 time_now = SDL_GetPerformanceCounter();
	Uint64 time_last = 0;
	double dt = 0;

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

		time_last = time_now;
		time_now = SDL_GetPerformanceCounter();

		dt = (double)((time_now - time_last) / (double)SDL_GetPerformanceFrequency());
		world.step(dt);

		mainShader.setMat4("projection", theCamera.projection());
		mainShader.setMat4("view_matrix", theCamera.gen_mat());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mainShader.setInt("mvc", ball.mvc); // forgot what this meant. main vector count?
		mainShader.setMat4("model", rigidbody1.getModelMatrix());
		ball.draw();
		mainShader.setMat4("model", rigidbody2.getModelMatrix());
		ball.draw();

		SDL_GL_SwapWindow(window);
	}

	return 0;
}
