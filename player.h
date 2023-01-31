#ifndef PLAYER_H
#define PLAYER_H

class Player: public entity {
    public:
        Player(int arrNum);
        void shoot();
        int getArrowsNum();
        bool getPlayerStatus();
        void setPlayerStatus(bool alive);
    private:
        bool isAlive;
        int numOfArrows;
};

#endif