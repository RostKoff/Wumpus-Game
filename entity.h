#ifndef ENTITY_H
#define ENTITY_H

class entity {
    public:
        void setCurrentPos(int newPos);
        int getCurrentPos();
    protected:
        int currentPosition;
};

#endif