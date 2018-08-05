#pragma once

#include "video/canvas.h"
#include "input/input.h"
#include "game_object/game_object.h"

class Scene {
public:
	Scene();
	virtual void init();
    virtual void update(Input *input);
    virtual void draw(Canvas *canvas);
	virtual void destroy();
};
