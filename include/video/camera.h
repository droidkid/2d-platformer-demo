#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

class Camera {
public:
	virtual SDL_Rect transform(SDL_Rect *playerBox) {
		return *playerBox;
	};
};