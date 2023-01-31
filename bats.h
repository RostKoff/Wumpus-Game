#ifndef BATS_H
#define BATS_H
#include "player.h"

class Bats: public entity {
    public:
        void encounter(Player* player);
};

#endif