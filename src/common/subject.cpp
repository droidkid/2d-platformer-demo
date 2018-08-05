#include "common/subject.h"

#define NULL 0

Subject::Subject() {
    for (int i=0; i < 10; i++) {
        observers[i] = NULL;
    }
}

void Subject::notify(int eventType) {
    for (int i=0; i < 10; i++) {
        if (observers[i] != NULL) {
            observers[i]->onEvent(eventType);
        }
    }
}

void Subject::addObserver(Observer *observer) {
    for (int i=0; i < 10; i++) {
        if (observers[i] == NULL) {
            observers[i] = observer;
            return;
        }
    }
}

void Subject::removeObserver(Observer *observer) {
    for (int i=0; i < 10; i++) {
        if (observers[i] == observer) {
            observers[i] = NULL;
        }
    }
}
