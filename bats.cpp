#include <iostream>
#include "entity.h"
#include "bats.h"
#include "player.h"

// The function executes encounter with the bat. 
void Bats::encounter(Player* player) {
    std::cout<<"\nZIIIP... Super Bat teleported you to another place...";
    while (1) {
        // The player is teleported to another room of the cave.
        player->setCurrentPos(rand()%20);
        // Ensuring that the player will not be teleported to the same room from which he was teleported.
        if(player->getCurrentPos() != currentPosition) 
            break;
    }
    
}