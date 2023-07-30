#pragma once

#include <iostream>

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera {
public:
	glm::vec2 camera_pos = {0, 0};
	float camera_zoom = 1.0;

	glm::mat4 gen_mat();
	glm::mat4 projection();

	void mousedown_ev(SDL_MouseButtonEvent ev);
	void mouseup_ev(SDL_MouseButtonEvent ev);
	void mousemove_ev(SDL_MouseMotionEvent ev);
	void mousewheel_ev(SDL_MouseWheelEvent ev);
private:
	bool pressed = false;
	glm::vec2 origin = { 0, 0 };
	glm::vec2 origin_campos = { 0, 0 };
	std::pair<float, float> winres = { 800, 600 };
};