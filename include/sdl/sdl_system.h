#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class SDLSystem
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	void initLibs();
	void createWindow(int width, int height);

public:
	SDLSystem(int width, int height);
	~SDLSystem();
	SDL_Renderer* getRenderer();
};
