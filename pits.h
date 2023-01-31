#ifndef PITS_H
#define PITS_H
#include "player.h"

class Pits: public entity {
    public:
        void encounter(Player* player);
};

#endif