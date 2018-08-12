#include "video/camera.h"

#include "game_constants.h"
using namespace GameConstants;

class WorldCamera:public Camera {
public:
	int x;
	int y;
	WorldCamera() {
		x = 0;
		y = 0;
	}

	void setXY(int x, int y) {
		this->x = x;
		this->y = y;
	}

	SDL_Rect transform(SDL_Rect *playerObject) {

		SDL_Rect ret = {
			playerObject->x,
			playerObject->y,
			playerObject->w,
			playerObject->h
		};

		ret.x -= x;
		ret.y -= y;

		return ret;
	}
};