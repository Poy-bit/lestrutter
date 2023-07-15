#include <iostream>
#include <SDL.h>
#include "glad/glad.h"
#include <SDL_opengl.h>

int main(int argc, char* argv[]) {
	std::cout << "Hello, world!\n";

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window* window = SDL_CreateWindow("Wow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

	//SDL_GLContext gContext = SDL_GL_CreateContext(window);

	return 0;
}
