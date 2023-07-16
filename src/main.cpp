#include <iostream>
#include <SDL.h>
#include "glad/glad.h"

#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include "shader.h"

using namespace glm;

const float WIN_WIDTH = 800;
const float WIN_HEIGHT = 600;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO); // TODO: Add to tests

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window* window = SDL_CreateWindow("Lestrutter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	SDL_GLContext gl_context = SDL_GL_CreateContext(window); // TODO: Add to tests
	SDL_GL_MakeCurrent(window, gl_context);

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	SDL_GL_SetSwapInterval(1); // Important Apparently

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress); // TODO: Add to tests

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	GLuint VAO;
	GLuint VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (void*)&vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	shader mainShader = shader(SOURCE_PATH+std::string("/res/shaders/vert.txt"), SOURCE_PATH+std::string("/res/shaders/frag.txt"));
	mainShader.bind();

	vec2 origin = {0, 0};
	vec2 origin_campos = { 0, 0 };
	vec2 campos = {0, 0};

	bool pressed = false;

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case (SDL_QUIT): { quit = true; break; }
			case (SDL_MOUSEBUTTONDOWN): {
				origin = { e.button.x / (WIN_WIDTH/2)-1, 1-e.button.y / (WIN_HEIGHT/2)-1 };
				pressed = true;  break;
			} case (SDL_MOUSEBUTTONUP): {
				origin_campos = campos;
				pressed = false;  break;
			} case (SDL_MOUSEMOTION): {
				if (pressed) {
					vec2 rel_pos = vec2(e.motion.x / (WIN_WIDTH / 2) - 1, 1-e.motion.y / (WIN_HEIGHT / 2) - 1);
					campos = origin_campos + (rel_pos - origin); }
			}
			}
		}

		mat4 cammat = translate(mat4(1.0f), vec3(campos, 0.0f));
		mainShader.setMat4("cammat", cammat);

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(window);
	}

	return 0;
}
