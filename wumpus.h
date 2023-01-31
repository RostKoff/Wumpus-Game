#ifndef WUMPUS_H
#define WUMPUS_H
#include "player.h"
class Wumpus: public entity {
    public:
        Wumpus(bool sleep, int active);
        bool getSleepStatus();
        void setSleepStatus(bool sleep);
        bool getWumpusStatus();
        void setWumpusStatus(bool alive);
        void encounter(Player* player, const int* room);
        void roam(const int* room);
        void roam(const int* room, int customProbability);
    private:
        bool isAlive;
        bool isAsleep;
        int activeness;
};

#endif