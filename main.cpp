#include <iostream>

const short int cave[20][3] = {{1, 7, 4}, {2, 9, 0}, {3, 11, 1}, {4, 13, 2}, {0, 5, 3},
                  {14, 4, 6}, {7, 16, 5}, {6, 0, 8}, {9, 17, 7}, {8, 1, 10},
                  {11, 18, 9}, {10, 2, 12}, {13, 19, 11}, {12, 3, 14}, {5, 15, 13},
                  {19, 14, 16}, {15, 6, 17}, {16, 8, 18}, {17, 10, 19}, {18, 12, 15}};

bool connectedRooms(int room, int element);

class entity {
    public:
        void setCurrentPos(short int pos);\
        short int getCurrentPos();
    protected:
        short int current_position = 0;
};

void entity::setCurrentPos(short int pos) {
    current_position = pos;
}

short int entity::getCurrentPos() {
    return current_position;
}

class Player: public entity {
    public:
        void move(int new_pos);
        void shoot(int pos);
        short int getArrows();
    private:
        short int num_of_arrows = 3;
};

void Player::move(int new_pos) {
    if(connectedRooms(current_position, new_pos)) current_position = new_pos;
}


void Player::shoot(int pos) {
    if(connectedRooms(current_position, pos)) {
        std::cout<<"Arrow in "<<pos<<"\n";
        num_of_arrows--;
    }
    else std::cout<<"Wrong room\n";
}

short int Player::getArrows() {
    return num_of_arrows;
}

void chooseOption(Player* player);

int main() {
    Player player;
    while (1) {
        chooseOption(&player);   
    }
    return 0;
}

bool connectedRooms(int room, int element) {
    for(int i=0; i<3; i++) 
        if(cave[room][i] == element) return 1;
    return 0;
}

void chooseOption(Player* player) {
    char option;
    int room;
    std::cout<<"You are in room "<<player->getCurrentPos();
    std::cout<<"\nArrows left: "<<player->getArrows();
    std::cout<<"\nTunnels lead to: ";
    for(int i=0; i<3; i++) {
        std::cout<<cave[player->getCurrentPos()][i]<<" ";
    }
    std::cout<<"\nShoot or move[s/m]?: ";
    std::cin>>option;
    
    switch (option) {
    case 'm':
        std::cout<<"Where to?: ";
        std::cin>>room;
        player->move(room);
        break;
    case 's':
        std::cout<<"Where to?: ";
        std::cin>>room;
        player->shoot(room);
        break;
    default:
        std::cout<<"Wrong option!\n";
        break;
    }
    return;
}

