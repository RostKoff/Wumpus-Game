#include "entity.h"

// The function sets the current position of the entity
void entity::setCurrentPos(int newPos) {
    currentPosition = newPos;
}

// The function gets the current position of the entity
int entity::getCurrentPos() {
    return currentPosition;
}