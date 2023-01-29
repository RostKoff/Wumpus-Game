#include <iostream>

const int cave[20][3] = {{1, 7, 4}, {2, 9, 0}, {3, 11, 1}, {4, 13, 2}, {0, 5, 3},
                  {14, 4, 6}, {7, 16, 5}, {6, 0, 8}, {9, 17, 7}, {8, 1, 10},
                  {11, 18, 9}, {10, 2, 12}, {13, 19, 11}, {12, 3, 14}, {5, 15, 13},
                  {19, 14, 16}, {15, 6, 17}, {16, 8, 18}, {17, 10, 19}, {18, 12, 15}};

bool connectedRooms(int room, int element);

class entity {
    public:
        void setCurrentPos(int pos);\
        int getCurrentPos();
    protected:
        int currentPosition = 0;
};

void entity::setCurrentPos(int pos) {
    currentPosition = pos;
}

int entity::getCurrentPos() {
    return currentPosition;
}

class Player: public entity {
    public:
        void move(int newPos);
        void shoot();
        int getArrowsNum();
    private:
        int numOfArrows = 3;
};

void Player::move(int newPos) {
    currentPosition = newPos;
}

void Player::shoot() {
    numOfArrows--;
}

int Player::getArrowsNum() {
    return numOfArrows;
}

void menu();
void game();

int main() {
    menu();
    return 0;
}

bool connectedRooms(int room, int element) {
    for(int i=0; i<3; i++) 
        if(cave[room][i] == element) return 1;
    return 0;
}

void menu() {
    while (1) {
        char option;
        std::cout<<"[1] Start game\n[2] Instructions\n[q] Quit\nOption?: ";
        std::cin>>option;
        if(option == 'q') break;
        switch (option) {
        case '1':
            game();
            break;
        case '2':
            std::cout<<"Hello guys!\nPress any key to continue...\n";
            _getwch();
            break;  
        default:
            std::cout<<"Wrong option!\n";
            break;
        }
    }
    
}

void game() {
    Player player;
    char option;
    int selectedRoom;
    bool gameOver = 0;

    std::cout<<"Note: You can always quit with typing [q]\n";
    while(!gameOver) {
        std::cout<<"\nYou are in room "<<player.getCurrentPos();
        std::cout<<"\n\tArrows left: "<<player.getArrowsNum();
        std::cout<<"\nTunnels lead to: ";
        for(int i=0; i<3; i++) {
            std::cout<<cave[player.getCurrentPos()][i]<<" ";
        }
        std::cout<<"\nShoot or move[s/m]?: ";

        std::cin>>option;
        
        switch (option) {
        case 'm':
            std::cout<<"Where to?: ";
            std::cin>>selectedRoom;
            if(connectedRooms(player.getCurrentPos(), selectedRoom)) 
                player.move(selectedRoom);
            break;
        case 's':
            std::cout<<"Where to?: ";
            std::cin>>selectedRoom;
            
            if(connectedRooms(player.getCurrentPos(), selectedRoom)) { 
                std::cout<<"Arrow in "<<selectedRoom<<"\n";
                player.shoot();

                if(player.getArrowsNum() == 0) {
                    std::cout<<"Out of Arrows!\nYou lose!\nPress any key to continue...\n";
                    _getwch();
                    gameOver = 1;
                }
                        
            }
            else 
                std::cout<<"Wrong room\n";
            break;
        case 'q':
            gameOver = 1;
            break;
        default:
            std::cin.ignore(1000, '\n');
            std::cout<<"Wrong option!\n";
            break;
        }
    }
}