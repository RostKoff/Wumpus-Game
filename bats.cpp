#include <iostream>
#include "entity.h"
#include "bats.h"
#include "player.h"

void Bats::encounter(Player* player) {
    std::cout<<"\nZIIIP... Super Bat teleported you to another place...";
    while (1) {
        player->setCurrentPos(rand()%20);
        if(player->getCurrentPos() != currentPosition) 
            break;
    }
    
}