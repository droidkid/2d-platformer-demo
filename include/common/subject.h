#pragma once

#include "observer.h"
#include "engine/game_engine_constants.h"

using namespace GameEngineConstants;

class Subject {
	// Make this a linked list.
    Observer *observers[MAX_GAME_OBJECTS];
    protected:
        void notify(int eventType);
    public:
        Subject();
        void addObserver(Observer *observer);
        void removeObserver(Observer *observer);
};
