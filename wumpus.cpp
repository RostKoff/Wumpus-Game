#include <iostream>
#include "entity.h"
#include "wumpus.h"
#include "player.h"

Wumpus::Wumpus(bool sleep, int active) {
    isAsleep = sleep;
    activeness = active;
    isAlive = 1;
}

bool Wumpus::getSleepStatus() {
    return isAsleep;
}

void Wumpus::setSleepStatus(bool sleep) {
    isAsleep = sleep;
}

bool Wumpus::getWumpusStatus() {
    return isAlive;
}

void Wumpus::setWumpusStatus(bool alive) {
    isAlive = alive;
}

void Wumpus::encounter(Player* player, const int* room) {
    int randNum;

    if(isAsleep == 1) {
        isAsleep = 0;
        randNum = (rand()%100)+1;
        if(randNum > activeness) {
            roam(room, 100);
            return;
        }
    }

    std::cout<<"\nHA-HA-HA! Wumpus got you!";
    player->setPlayerStatus(0);
}

void Wumpus::roam(const int* room) {
    int randNum = (rand()%100)+1;

    if(randNum <= activeness) {
        setCurrentPos(*(room+rand()%3));
    }
}

void Wumpus::roam(const int* room, int customProbability) {
    int randNum = (rand()%100)+1;

    if(randNum <= customProbability) {
        setCurrentPos(*(room+rand()%3));
    }
}