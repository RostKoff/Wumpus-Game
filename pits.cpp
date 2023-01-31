#include <iostream>
#include "entity.h"
#include "pits.h"
#include "player.h"

void Pits::encounter(Player* player) {
    std::cout<<"\nOops! You fell into the pit!";
    player->setPlayerStatus(0);
}