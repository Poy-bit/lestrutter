#include <iostream>
#include <SDL.h>
#include "glad/glad.h"

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

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				std::cout << "QUIT\n";
				quit = true;
			} else if (e.type == SDL_TEXTINPUT) {
				int x = 0, y = 0;
				SDL_GetMouseState(&x, &y);
				std::cout << e.text.text[0];
				//handleKeys(e.text.text[0], x, y);
			}
			
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(window);
	}

	return 0;
}
