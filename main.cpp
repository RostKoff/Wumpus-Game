#include <iostream>
#include <algorithm>
#include <time.h>
#include "entity.h"
#include "player.h"
#include "wumpus.h"
#include "bats.h"
#include "pits.h"

// The 'Cave' array defines the map and navigation on it.
// The first dimension is responsible for the room number, and the second for the rooms you can go to.
const int cave[20][3] = {{1, 7, 4}, {2, 9, 0}, {3, 11, 1}, {4, 13, 2}, {0, 5, 3},
                  {14, 4, 6}, {7, 16, 5}, {6, 0, 8}, {9, 17, 7}, {8, 1, 10},
                  {11, 18, 9}, {10, 2, 12}, {13, 19, 11}, {12, 3, 14}, {5, 15, 13},
                  {19, 14, 16}, {15, 6, 17}, {16, 8, 18}, {17, 10, 19}, {18, 12, 15}};

void menu();
void game();
bool connectedRooms(int firstRoom, int secondRoom);
int getFreeRoom(int* list, int size);
void printInstructions();

int main() {
    menu();
    return 0;
}

void menu() {
    while (1) {
        char option;

        // Outputting menu options.
        std::cout<<"\n[1] Start game\n[2] Instructions\n[q] Quit\nOption?: ";

        // Selecting an option.
        std::cin>>option;
        if(option == 'q') break;
        switch (option) {
        case '1':
            game();
            break;
        case '2':
            printInstructions();
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

    char option;
    int selectedRoom;
    int tempPos;

    // Declaration of an array that will contain rooms already occupied by entities.
    int listSize = 2+(sizeof(bats)/sizeof(bats[0]))+(sizeof(pits)/sizeof(pits[0]));
    int reservedList[listSize];

    // Filling the array with '-1', which will mean that the room is free.
    std::fill_n(reservedList, listSize, -1);

    srand(time(NULL));

    // Placing each entity in a randomly selected room.
    player.setCurrentPos(getFreeRoom(reservedList, listSize));
    wumpus.setCurrentPos(getFreeRoom(reservedList, listSize));
    for(int i=0; i<(sizeof(bats)/sizeof(bats[0])); i++)
        bats[i].setCurrentPos(getFreeRoom(reservedList, listSize));
    for(int i=0; i<sizeof(pits)/sizeof(pits[0]); i++)
        pits[i].setCurrentPos(getFreeRoom(reservedList, listSize));


    std::cout<<"\nNote: Type [q] to exit\n";

    // Start of a loop that will run as long as both the player and the Wumpus are alive.
    while(player.getPlayerStatus() && wumpus.getWumpusStatus()) {

        // Checking whether the player is in the same room as other creatures
        // and executing the encounter function if so.
        // If the encounter function is executed, the loop starts from the beginning.
        if(wumpus.getCurrentPos() == player.getCurrentPos()) {
            wumpus.encounter(&player, cave[wumpus.getCurrentPos()]);
            continue;
        }
        // Declaring the player's position in the 'tempPos' variable before IF statement 
        // to understand whether an encounter with bats has occurred. 
        tempPos = player.getCurrentPos();
        for(int i=0; i<sizeof(bats)/sizeof(bats[0]); i++)
            if(bats[i].getCurrentPos() == player.getCurrentPos()) {
                bats[i].encounter(&player);
                break;
            }

        // If player's position before IF statement differ from current position
        // the program returns to the beginning of the loop.
        if (tempPos != player.getCurrentPos())
            continue;
        
        for(int i=0; i<sizeof(pits)/sizeof(pits[0]); i++)
            if(pits[i].getCurrentPos() == player.getCurrentPos()) {
                pits[i].encounter(&player);
                break;
            }

        // If the player died as a result of an encounter with the pits, 
        // the program returns to the beginning of the loop.  
        if(!player.getPlayerStatus())
            continue; 

        
        // Start of information output for the player.
        std::cout<<"\nYou are in room "<<player.getCurrentPos();

        // Checking for creatures in rooms connected to the player's room.
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
        // End of information output.

        std::cout<<"\nShoot or move[s/m]?: ";
        std::cin>>option;
        
        if(option == 'q') 
            break;

        switch (option) {
        case 'm':
            // Movement to the selected room only if it is connected to the current room.
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
            // Shooting to the selected room only if it is connected to the current room. 
            std::cout<<"Where to?: ";
            std::cin>>selectedRoom;
            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            if(connectedRooms(player.getCurrentPos(), selectedRoom)) { 
                std::cout<<"\nYou shoot in room "<<selectedRoom;
                // If the selected room is occupied by Wumpus, he dies and loop ends.
                if(selectedRoom == wumpus.getCurrentPos()) {
                    std::cout<<"\nYou got the Wumpus!";
                    wumpus.setWumpusStatus(0); 
                    break;
                }
                // If the selected room is not occupied by a Wumpus, 
                // but the Wumpus's room is connected to the Player's room, the Wumpus wakes up.
                else if(connectedRooms(wumpus.getCurrentPos(), player.getCurrentPos()) && wumpus.getSleepStatus()) {
                    std::cout<<"\nThe beast has awoken";
                    wumpus.setSleepStatus(0);    
                }
                // In other cases, information appears that nothing happened.
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
        // If Wumpus is awake, the roam function executes.
        if(!wumpus.getSleepStatus())
            wumpus.roam(cave[wumpus.getCurrentPos()]);    
    }

    // Displaying information about the end of the game if the player is dead.
    if(!player.getPlayerStatus()) {
        std::cout<<"\nYou lose!\nPress any key to continue...";
        _getwch();
    }

    // Displaying information about the end of the game if the wumpus is dead.
    else if(!wumpus.getWumpusStatus()) {
        std::cout<<"\nYou won!\nWumpus will get you next time!\nPress any key to continue...";
        _getwch();
    }
}

// A function that checks if the elements of the first room are equal to the second room number.
bool connectedRooms(int firstRoom, int secondRoom) {
    for(int i=0; i<3; i++) 
        if(cave[firstRoom][i] == secondRoom) 
            return 1;
    return 0;
}

// A function that returns a randomly selected room if it does not appear in the given list.
int getFreeRoom(int* list, int size) {
    // Declaring a variable for storing a randomly selected room.
    int randValue;
    
    while (1) {
        randValue = rand()%20;

        // Loop for checking given list.
        for(int i=0; i<size; i++) {
            // '-1' in the list means that other elements of the list are free and the room can be returned.
            if(*(list+i) == -1) {
                *(list+i) = randValue;
                return randValue;
            }
            // If the 'randValue' variable equals an element in the list,
            // a new room is selected and the list check starts over.
            else if(randValue == *(list+i)) 
                break;
        }
    }
}

// The function outputs game instructions for the player.
void printInstructions() {
    std::cout<<"\nWelcome to \'Hunt The Wumpus\'\nThe Wumpus lives in a cave of 20 rooms.\nEach room has 3 tunnels leading to other rooms.\n\nHazards:\nBottomless pits - some rooms have bottomless pits in them.\nIf you go there, you fall into the pit (& lose!).\nSuper bats - two other rooms have super bats.\nIf you go there, a bat grabs you and takes you to some other\nroom at random.(which may be troublesome)\n\nWumpus:\nThe Wumpus is not bothered by hazards and usually he is asleep.\nTwo things wake him up:\nYou shooting an arrow near him or you entering his room.\nIf the Wumpus wakes, he may move one room or stays still.\nAfter that, if he is where you are, he eats you up and you lose!\n\nYou:\nEach turn you may move or shoot an arrow\nMoving: you can move through one tunnel.\nShooting: you can shoot through one tunnel.\nYou lose when you run out of arrows.\nIf the arrow hits the wumpus, you win.\n\nPress any key to continue...\n";
    _getwch();
}

