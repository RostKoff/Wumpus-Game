#include <iostream>
#include "entity.h"
#include "wumpus.h"
#include "player.h"

// Sleep state and activity in percentage are required as arguments to the constructor.
Wumpus::Wumpus(bool sleep, int active) {
    isAsleep = sleep;
    activeness = active;
    isAlive = 1;
}

// The function returns 'true' if the Wumpus is asleep and 'false' if the wumpus is not
bool Wumpus::getSleepStatus() {
    return isAsleep;
}

// The function sets the sleep state of the Wumpus
void Wumpus::setSleepStatus(bool sleep) {
    isAsleep = sleep;
}

// The function returns 'true' if the Wumpus is alive and 'false' if the Wumpus is dead
bool Wumpus::getWumpusStatus() {
    return isAlive;
}

// The function sets the status of whether Wumpus is alive
void Wumpus::setWumpusStatus(bool alive) {
    isAlive = alive;
}

// The function executes encounter with the Wumpus. 
// Pointers to the player and to the current room are required as arguments.
void Wumpus::encounter(Player* player, const int* room) {
    // Declaring a variable for storing a randomly selected number from 1 to 100.
    int randNum;

    // If Wumpus was asleep, he awakes
    if(isAsleep == 1) {
        std::cout<<"\nThe beast has awoken";
        isAsleep = 0;
        
        randNum = (rand()%100)+1;

        // If the 'randNum' value is greater than the 'activeness' value, Wumpus will go to another room
        // instead of killing the player
        if(randNum > activeness) {
            roam(room, 100);
            return;
        }
    }

    std::cout<<"\nHA-HA-HA! Wumpus got you!";
    player->setPlayerStatus(0);
}

// The Wumpus with a probability dependent on the 'activeness' variable 
// will move to one of the connected rooms.
// The current Wumpus room is required as an argument. 
void Wumpus::roam(const int* room) {
    int randNum = (rand()%100)+1;

    if(randNum <= activeness) {
        setCurrentPos(*(room+rand()%3));
    }
}

// The Wumpus with a probability dependent on the 'customProbability' argument 
// will move to one of the connected rooms.
// The current Wumpus room is required as the first argument. 
void Wumpus::roam(const int* room, int customProbability) {
    // Declaring a variable for storing a randomly selected number from 1 to 100.
    int randNum = (rand()%100)+1;

    if(randNum <= customProbability) {
        setCurrentPos(*(room+rand()%3));
    }
}