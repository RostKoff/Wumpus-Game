#include <iostream>
#include "entity.h"
#include "player.h"

// The number of arrows is required as an argument to the constructor
Player::Player(int arrNum) {
    isAlive = 1;
    numOfArrows = arrNum;
}

// A function that reduces the number of arrows and checks whether the player has run out of them
void Player::shoot() {
    numOfArrows--;
    
    // Player dies when he is run out of arrows
    if(numOfArrows <= 0) {
        std::cout<<"\nOut of arrows!";
        isAlive = 0;        
    }
}

// The function returns the number of arrows of the player.
int Player::getArrowsNum() {
    return numOfArrows;
}

// The function returns 'true' if the player is alive and 'false' if the player is dead
bool Player::getPlayerStatus() {
    return isAlive;
}

// The function sets the status of whether player is alive.
void Player::setPlayerStatus(bool alive) {
    isAlive = alive;
}