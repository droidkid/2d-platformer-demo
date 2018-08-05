#pragma once

#include "input/input_poller.h"
#include "video/canvas.h"
#include "scene/scene.h"

class GameLoop {
    int currentTickMs;
    int lagMs;
	int lastDrawFrame;
    InputPoller *inputPoller;
    Canvas *canvas;

public:
    GameLoop ( InputPoller *inputPoller, Canvas *canvas );
    void runLoop ( Scene *scene );
};
