#include <iostream>
#include <algorithm>
#include <time.h>
#include "entity.h"
#include "player.h"
#include "wumpus.h"
#include "bats.h"
#include "pits.h"

const int cave[20][3] = {{1, 7, 4}, {2, 9, 0}, {3, 11, 1}, {4, 13, 2}, {0, 5, 3},
                  {14, 4, 6}, {7, 16, 5}, {6, 0, 8}, {9, 17, 7}, {8, 1, 10},
                  {11, 18, 9}, {10, 2, 12}, {13, 19, 11}, {12, 3, 14}, {5, 15, 13},
                  {19, 14, 16}, {15, 6, 17}, {16, 8, 18}, {17, 10, 19}, {18, 12, 15}};

bool connectedRooms(int room, int element);
void menu();
void game();
int getFreeRoom(int* list, int size);

int main() {
    menu();
    return 0;
}

bool connectedRooms(int room, int element) {
    for(int i=0; i<3; i++) 
        if(cave[room][i] == element) 
            return 1;
    return 0;
}

void menu() {
    while (1) {
        char option;
        std::cout<<"\n[1] Start game\n[2] Instructions\n[q] Quit\nOption?: ";
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
    Player player(3);
    Wumpus wumpus(1, 50);
    Bats bats[2];
    Pits pits[2];
    int tempPos;
    int listSize = 2+(sizeof(bats)/sizeof(bats[0]))+(sizeof(pits)/sizeof(pits[0]));
    int reservedList[listSize];
    char option;
    int selectedRoom;

    std::fill_n(reservedList, listSize, -1);

    srand(time(NULL));

    player.setCurrentPos(getFreeRoom(reservedList, listSize));
    wumpus.setCurrentPos(getFreeRoom(reservedList, listSize));
    for(int i=0; i<(sizeof(bats)/sizeof(bats[0])); i++)
        bats[i].setCurrentPos(getFreeRoom(reservedList, listSize));
    for(int i=0; i<sizeof(pits)/sizeof(pits[0]); i++)
        pits[i].setCurrentPos(getFreeRoom(reservedList, listSize));

 
    std::cout<<"\nNote: Type [q] to exit\n";
    while(player.getPlayerStatus() && wumpus.getWumpusStatus()) {


        if(wumpus.getCurrentPos() == player.getCurrentPos()) {
            wumpus.encounter(&player, cave[wumpus.getCurrentPos()]);
            continue;
        }
        tempPos = player.getCurrentPos();
        for(int i=0; i<sizeof(bats)/sizeof(bats[0]); i++)
            if(bats[i].getCurrentPos() == player.getCurrentPos()) {
                bats[i].encounter(&player);
                break;
            }
        if (tempPos != player.getCurrentPos())
            continue;
        
        for(int i=0; i<sizeof(pits)/sizeof(pits[0]); i++)
            if(pits[i].getCurrentPos() == player.getCurrentPos()) {
                pits[i].encounter(&player);
                break;
            }
        if(!player.getPlayerStatus())
            continue; 


        std::cout<<"\nYou are in room "<<player.getCurrentPos();


        if(connectedRooms(wumpus.getCurrentPos(), player.getCurrentPos())) 
            std::cout<<"\n\tI can feel the Wumpus!";
        
        for(int i=0; i<sizeof(bats)/sizeof(bats[0]); i++)
            if(connectedRooms(bats[i].getCurrentPos(), player.getCurrentPos())) {
                std::cout<<"\n\tBats nearby!";
                break;
            }
        for(int i=0; i<sizeof(pits)/sizeof(pits[0]); i++)
            if(connectedRooms(pits[i].getCurrentPos(), player.getCurrentPos())) {
                std::cout<<"\n\tI feel a draft!";
                break;
            }

        
        std::cout<<"\n\tArrows left: "<<player.getArrowsNum()<<".";
        std::cout<<"\nTunnels lead to: ";
        for(int i=0; i<3; i++) {
            std::cout<<cave[player.getCurrentPos()][i]<<" ";
        }
        std::cout<<"\nShoot or move[s/m]?: ";

        std::cin>>option;
        
        if(option == 'q') 
            break;

        switch (option) {
        case 'm':
            while (1) {
                std::cout<<"Where to?: ";
                std::cin>>selectedRoom;
                if(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                if(connectedRooms(player.getCurrentPos(), selectedRoom)) {
                    player.setCurrentPos(selectedRoom);
                    break;
                }
                std::cout<<"Not possible\n";
            }
            break;
        case 's':
            while(1) {
            std::cout<<"Where to?: ";
            std::cin>>selectedRoom;
            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            if(connectedRooms(player.getCurrentPos(), selectedRoom)) { 
                std::cout<<"\nYou shoot in room "<<selectedRoom;
                if(selectedRoom == wumpus.getCurrentPos()) {
                    std::cout<<"\nYou got the Wumpus!";
                    wumpus.setWumpusStatus(0); 
                    break;
                }
                else if(connectedRooms(wumpus.getCurrentPos(), player.getCurrentPos()) && wumpus.getSleepStatus()) {
                    std::cout<<"\nThe beast has awoken";
                    wumpus.setSleepStatus(0);    
                }
                else 
                    std::cout<<"\nNothing happened...";
                player.shoot();
                break;
            }
            
            std::cout<<"Not possible.\n";
            }
            break;
        default:
            std::cout<<"Wrong option!\n";
            break;
        }

        if(!wumpus.getSleepStatus())
            wumpus.roam(cave[wumpus.getCurrentPos()]);    
    }

    if(!player.getPlayerStatus()) {
        std::cout<<"\nYou lose!\nPress any key to continue...";
        _getwch();
    }
    else if(!wumpus.getWumpusStatus()) {
        std::cout<<"\nYou won!\nWumpus will get you next time!\nPress any key to continue...";
        _getwch();
    }
}

int getFreeRoom(int* list, int size) {
    int randValue;
    
    while (1) {
        randValue = rand()%20;
        for(int i=0; i<size; i++) {
            if(*(list+i) == -1) {
                *(list+i) = randValue;
                return randValue;
            } 
            else if(randValue == *(list+i)) 
                break;
        }
    }
}

