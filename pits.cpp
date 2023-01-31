#include <iostream>
#include "entity.h"
#include "pits.h"
#include "player.h"

// The function executes encounter with the pit. 
void Pits::encounter(Player* player) {
    std::cout<<"\nOops! You fell into the pit!";
    player->setPlayerStatus(0);
}