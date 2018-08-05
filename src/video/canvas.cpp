#include "video/canvas.h"


Canvas::Canvas(SDLSystem * sdl) {
	this->renderer = sdl->getRenderer();
}

void Canvas::clearScreen() {
	SDL_RenderClear(renderer);
}

void Canvas::renderScreen() {
	SDL_RenderPresent(renderer);
}

void Canvas::drawText(char *text, int x, int y, TTF_Font *font, SDL_Color textColor) {
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect boundingBox;
	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = textSurface->w;
	boundingBox.h = textSurface->h;

	SDL_RenderCopy(renderer, texture, NULL, &boundingBox);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);
}

void Canvas::drawTexture(SDL_Texture *texture, SDL_Rect *boundingBox) {
	SDL_RenderCopy(renderer, texture, NULL, boundingBox);
}

void Canvas::drawTextureHFlip(SDL_Texture *texture, SDL_Rect *boundingBox) {
	SDL_RenderCopyEx(renderer, texture, NULL, boundingBox, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void Canvas::drawTexture(SDL_Texture *texture, SDL_Rect boundingBox) {
	drawTexture(texture, &boundingBox);
}

void Canvas::drawTextureHFlip(SDL_Texture *texture, SDL_Rect boundingBox) {
	drawTextureHFlip(texture, &boundingBox);
}
