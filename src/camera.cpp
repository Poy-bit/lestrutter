#include "camera.h"

glm::mat4 camera::gen_mat() {
	glm::mat4 mat = glm::scale(glm::mat4(1.0f), glm::vec3(camera_zoom, camera_zoom, 1));
	mat = glm::translate(mat, glm::vec3(camera_pos * glm::vec2(1.0, 0.75), -1.0));
	return mat;
}

glm::mat4 camera::projection() {
	return glm::ortho(-1.0f, 1.0f, -0.75f, 0.75f, 0.01f, 300.0f);
}

void camera::mousedown_ev(SDL_MouseButtonEvent ev) {
	origin = { ev.x / (winres.first / 2) - 1, 1 - ev.y / (winres.second / 2) - 1 };
	pressed = true;
}
void camera::mouseup_ev(SDL_MouseButtonEvent ev) {
	origin_campos = camera_pos;
	pressed = false;
}
void camera::mousemove_ev(SDL_MouseMotionEvent ev) {
	if (pressed) {
		glm::vec2 rel_pos = glm::vec2(ev.x / (winres.first / 2) - 1, 1 - ev.y / (winres.second / 2) - 1);
		camera_pos = origin_campos + (rel_pos - origin) / camera_zoom;
	}
}
void camera::mousewheel_ev(SDL_MouseWheelEvent ev) {
	camera_zoom = std::min(std::max(camera_zoom + (camera_zoom * ev.preciseY) / 8, 0.01f), 4.0f);
}