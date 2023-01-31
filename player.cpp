#include <iostream>
#include "entity.h"
#include "player.h"

Player::Player(int arrNum) {
    isAlive = 1;
    numOfArrows = arrNum;
}

void Player::shoot() {
    numOfArrows--;
    
    if(numOfArrows <= 0) {
        std::cout<<"\nOut of arrows!";
        isAlive = 0;        
    }
}

int Player::getArrowsNum() {
    return numOfArrows;
}

bool Player::getPlayerStatus() {
    return isAlive;
}

void Player::setPlayerStatus(bool alive) {
    isAlive = alive;
}