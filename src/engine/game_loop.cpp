#include <SDL.h>

#include "engine/game_engine_constants.h"
#include "engine/game_loop.h"

using namespace GameEngineConstants;

GameLoop::GameLoop(InputPoller *inputPoller, Canvas *canvas) :
	inputPoller(inputPoller), canvas(canvas) {
	lagMs = 0;
	currentTickMs = 0;
}


void GameLoop::runLoop(Scene *scene) {
	bool quitEventReceived = false;
	currentTickMs = SDL_GetTicks();

	while (!quitEventReceived) {
		Input *input = new Input();
		inputPoller->pollInput(input);

		lagMs += SDL_GetTicks() - currentTickMs;
		currentTickMs = SDL_GetTicks();

		while (lagMs >= MS_PER_UPDATE) {
			scene->update(input);
			lagMs -= MS_PER_UPDATE;
		}

		scene->draw(canvas);

		quitEventReceived = input->quitEvent;
	}
}
