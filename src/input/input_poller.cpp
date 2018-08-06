#include <SDL.h>
#include "input/input_poller.h"

void InputPoller::pollInput(Input *input) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			input->quitEvent = true;
		}
	}
	SDL_GetMouseState(&(input->mouseX), &(input->mouseY));

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT]) {
		input->leftKeyDown = true;
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		input->rightKeyDown = true;
	}
	if (state[SDL_SCANCODE_RETURN]) {
		input->enterPressed = true;
	}
	if (state[SDL_SCANCODE_SPACE]) {
		input->spacePressed = true;
	}
	if (state[SDL_SCANCODE_LSHIFT]) {
		input->shiftPressed = true;
	}
}
