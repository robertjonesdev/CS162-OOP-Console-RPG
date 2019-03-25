/***************************************************************
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:   Game class implementation file.
***************************************************************/
#include <iostream>         //Console output
#include <fstream>
#include <iomanip>          //Console output formating
#include <vector>
#include <map>
#include "Menu.hpp"         //Input validation
#include "Game.hpp"
#include "Colors.hpp"       //Console colors
#include "LockedRoom.hpp"
#include "ItemRoom.hpp"
#include "MonsterRoom.hpp"
#include "Item.hpp"

using namespace std;

/******************************************************************************
** Constructor()
** Set member varibles to default value. Create the Map (Space Objects, Character)
** and the call the looping playGame function.
*******************************************************************************/
Game::Game()
{
    this->stepCounter = 0;
    this->hasVictory = false;
    createMap();
    playGame();
}

/******************************************************************************
** Destructor()
** Iterate through the map vector to delete the Space objects.
** Space objects will delete any item or monster objects they hold.
** Then delete the player. The player will delete any item objects it holds.
*******************************************************************************/
Game::~Game()
{
    for (size_t row = 0; row < gameMap.size(); row++)
    {
        for (size_t col = 0; col < gameMap[row].size(); col++)
        {
            delete gameMap[row][col];
        }
    }
    delete player;
}

/******************************************************************************
** createMap()
** This function allocated and links all the Space objects as a 2-D linked List.
** It also creates the Character object and adds the Item objects to the rooms.
** It is a private function called by the Game Constructor
*******************************************************************************/
void Game::createMap()
{
    ifstream inputFile;
    inputFile.open("map.txt");
    //First open the file and determine how many elements are in the file.
    if (inputFile.is_open())
    {
        int row = 0;
        int col = 0;
        char inChar;
        while(inputFile.get(inChar))
        {
            if (inChar == EOF || inChar == '\n')
            {   //New row in vector
                row++;
                col = 0;
            }
            else if (inChar == 'M')
            {   //Monster Room
                gameMap[row].push_back( new MonsterRoom());
                gameMap[row].back()->addMonster(new Monster("red dragon", 80));
                col++;
            }
            else if (inChar == 'o')
            {   //Item ROom with no Item
                gameMap[row].push_back( new ItemRoom());
                col++;
            }
            else if (inChar == 'P')
            {   //Item room with potion
                gameMap[row].push_back( new ItemRoom());
                gameMap[row].back()->addItem(new Item(301, 3, "healing potion"));
                col++;
            }
            else if (inChar == 'L')
            {   //Locked door to the north
                gameMap[row].push_back(new LockedRoom());
                col++;
            }
            else if (inChar == 'W')
            {   //Item Room with Weapon
                gameMap[row].push_back( new ItemRoom());
                gameMap[row].back()->addItem(new Item(201, 2, "longbow"));
                col++;
            }
            else if (inChar == 'K')
            {   //Item Room with Key
                gameMap[row].push_back( new ItemRoom());
                gameMap[row].back()->addItem(new Item(101, 1, "wooden key"));
                col++;
            }
            else if (inChar == 'S')
            {   //Item room and character start
                gameMap[row].push_back( new ItemRoom());
                this->startingSpace = gameMap[row].back();
                col++;
            }
            else
            {
                gameMap[row].push_back(nullptr);
                col++;
            }
        }
    }
    else
    {
        std::cout << "Error: could not access file." << std::endl;
        gameMenu.setQuit();
    }
    inputFile.close();

    //Link the objects together.
    for (size_t row = 0; row < gameMap.size(); row++)
    {
        for (size_t col = 0; col < gameMap[row].size(); col++)
        {
            if (gameMap[row][col] != nullptr)
            {
                //Set North
                if (row > 0 && gameMap[row - 1][col] != nullptr)
                    gameMap[row][col]->setNorth(gameMap[row - 1][col]);
                //Set east
                if (col < (gameMap[row].size()) && gameMap[row][col + 1] != nullptr)
                    gameMap[row][col]->setEast(gameMap[row][col + 1]);
                //Set South
                if (row < (gameMap.size() - 1) && gameMap[row + 1][col] != nullptr)
                    gameMap[row][col]->setSouth(gameMap[row + 1][col]);
                //Set West
                if (col > 0 && gameMap[row][col - 1] != nullptr)
                    gameMap[row][col]->setWest(gameMap[row][col - 1]);
            }
        }
    }

    //Create the character
    this->player = new Character("Myrddin Emrys", 100);
}

/******************************************************************************
** printgameMap()
** This function prints a static gameMap of the realm. It is a private function
** called by playGame().
*******************************************************************************/
void Game::printMap(Space* currentSpace)
{
    string mapkey[6];
    mapkey[0] = "O - Empty Room";
    mapkey[1] = "S - Starting Location";
    mapkey[2] = "I - Room with an Item";
    mapkey[3] = "M - Room with a Monster";
    mapkey[4] = "L - Room with a locked door";
    mapkey[5] = "X - Your Current Location";

    cout << "\n\tMap of the Realm\n"
         << "\t=-=-=-=-=-=-=-=-=\n\n\t";
    for (size_t row = 0; row < gameMap.size(); row++)
    {
        for (size_t col = 0; col < gameMap[row].size(); col++)
        {
            if (gameMap[row][col] != nullptr)
            {
                //Check West, If there is a room add a connecting bar
                if (col > 0 && gameMap[row][col - 1] != nullptr)
                    cout << "-";
                else
                    cout << " ";

                //Display indication of room type.
                if (gameMap[row][col] == currentSpace)
                    cout << BOLDRED << "X" << RESET;
                else if (gameMap[row][col]->hasItem())
                    cout << BOLDCYAN << "I" << RESET;
                else if (gameMap[row][col]->roomIsLocked())
                    cout << BOLDGREEN << "L" << RESET;
                else if (gameMap[row][col]->hasMonster())
                    cout << BOLDRED << "M" << RESET;
                else if (gameMap[row][col] == this->startingSpace)
                    cout << BOLDWHITE << "S" << RESET;
                else
                    cout << "O";

                //Check east,  If there is a room add a connecting bar
                if (col < (gameMap[row].size()) && gameMap[row][col + 1] != nullptr)
                    cout << "-";
                else
                    cout << " ";
            }
            else
                cout << "   ";
        }
        if (row < 6)
            cout << "\t" << mapkey[row];
        cout << "\n\t ";
        //Connecting lines in between north/south rooms
        for (size_t col = 0; col < gameMap[row].size(); col++)
        {
            if (col > 0)
                cout << " ";
            if (row < (gameMap.size() - 1) && gameMap[row][col] != nullptr && gameMap[row + 1][col] != nullptr)
                cout << "|";
            else
                cout << " ";
            if (col < gameMap[row].size())
                cout << " ";
        }
        cout << "\n\t";
    }
}

/******************************************************************************
** printMenu()
** This function prints the available options for the user. It is a private
** function called by playGame();
*******************************************************************************/
void Game::printMenu()
{
    const int width = 35;
    cout << "\n\t\t\t   Command List\n";
    cout.width((width * 2) + 5);
    cout.fill('-');
    cout << "-" << endl;
    cout.fill(' ');
    cout << left << setw(width) << "[n] [north]  Move North"   << " [d] [drop]    Drop Item\n"
         << left << setw(width) << "[e] [east]   Move East"    << " [u] [unlock]  Unlock door\n"
         << left << setw(width) << "[s] [south]  Move South"   << " [dr] [drink]  Use healing poition\n"
         << left << setw(width) << "[w] [west]   Move West"    << " [stats]       View stats & inventory\n"
         << left << setw(width) << "[g] [get]    Pickup Item"  << " [?] [help]    This Menu\n"
	     << left << setw(width) << "[q] [quit]   Quit game / Exit Realm\n"
         << "\n\n";
}

/******************************************************************************
** playGame()
** This is the game loop.
*******************************************************************************/
void Game::playGame()
{
    cout << YELLOW << "\n*Entering the Realm*\n" << RESET;
    gameMenu.getEnter();
    gameMenu.clearScreen();
    Space* currentSpace = this->startingSpace;

    cout << BOLDCYAN << "\nNewhaven, Village Entrance\n" << RESET;
    cout << "   Behind you lies the village of Newhaven. You are standing at the crude\n"
         << "wood gates of the village entrance. A bridge crosses a roaring stream underneath.\n"
         << "A low wooden palisade surrounds the village, to protect against creatures of the\n"
         <<  "night and random raiders. A dusty path leads to the north.\n\n"
         << "You open a scroll containing a map and notes you made to assist you in your journey...\n\n";
    printMap(currentSpace);
    printMenu();
    gameMenu.getEnter();

    while (!gameMenu.getQuit())
    {
        //First check if there is a monster in the room.
        checkForCombat(currentSpace);
        //If there is no monster in the room, and the player is alive:
        if (!this->hasVictory && !player->isDead())
        {
            currentSpace->printDescription();
            player->printHP();
            //In-Game Menu, get the user's choice and direct to correct function.
            switch (gameMenu.getCommand())
            {
                case 1: //Move North
                {
                    if (currentSpace->getNorth() != nullptr && !currentSpace->roomIsLocked())
                    {
                        cout << YELLOW << "\nMoving to the north...\n" << RESET;
                        currentSpace = currentSpace->getNorth();
                        addStep();
                    }
                    else
                        cout << "There is no exit in that direction!\n";
                    break;
                }
                case 2: //Move East
                {
                    if (currentSpace->getEast() != nullptr)
                    {
                        cout << YELLOW << "\nMoving to the east...\n" << RESET;
                        currentSpace = currentSpace->getEast();
                        addStep();
                    }
                    else
                        cout <<  "\nThere is no exit in that direction!\n";
                    break;
                }
                case 3: //Move South
                {
                    if (currentSpace->getSouth() != nullptr)
                    {
                        cout << YELLOW << "\nMoving to the south...\n" << RESET;
                        currentSpace = currentSpace->getSouth();
                        addStep();
                    }
                    else
                        cout <<  "\nThere is no exit in that direction!\n";
                    break;
                }
                case 4: //Move West
                {
                    if (currentSpace->getWest() != nullptr)
                    {
                        cout << YELLOW << "\nMoving to the west...\n" << RESET;
                        currentSpace = currentSpace->getWest();
                        addStep();
                    }
                    else
                        cout <<  "\nThere is no exit in that direction!\n";
                    break;
                }
                case 5: //Pickup item.
                {
                    Item* tempItem = currentSpace->takeItem();
                    if (tempItem != nullptr)
                    {
                        if (!player->addItem(tempItem))
                           currentSpace->addItem(tempItem);
                    }
                    else
                        cout << BOLDRED << "\nThere is no item here to pickup.\n" << RESET;
                    break;
                }
                case 6: //Drop item.
                {
                    Item* tempItem = player->removeItem();
                    if (tempItem != nullptr)
                        currentSpace->addItem(tempItem);
                    break;
                }
                case 7: //Unlock door.
                {
                    if (currentSpace->roomIsLocked())
                    {
                        Item* tempItem = player->useKey();
                        if (tempItem != nullptr)
                            currentSpace->unlockDoor(tempItem);
                    }
                    else
                        cout << BOLDRED <<"\nThere is not a door here to unlock!\n" << RESET;
                    break;
                }
                case 8: //drink the healing potion.
                {
                    player->usePotion();
                    break;
                }
                case 9: //view stats & inventory
                {
                    player->printStatsAndInv();
                    break;
                }
                case 10:
                {
                    printMap(currentSpace);
                    printMenu();
                    break;
                }
                case 11:
                {
                    cout << YELLOW << "\n*Exiting the realm!*\n" << RESET;
                    gameMenu.setQuit();
                    gameMenu.getEnter();
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        else if (this->hasVictory)
        {
            //Victory screen
            cout << BOLDGREEN << "\n  *You have won the game!*\n\n";
            gameMenu.setQuit();
            gameMenu.getEnter();
        }
        else
        {
            //Death / Game Over screen
            cout << BOLDRED << "\n  *You have died!*\n    *GAME OVER!*\n\n";
            gameMenu.setQuit();
            gameMenu.getEnter();
        }
    }
}
/******************************************************************************
** addStep()
** This function increments the stepCounter member variable. Every 5 steps,
** tell the player it is thirsty.
*******************************************************************************/
void Game::addStep()
{
    this->stepCounter++;
    //every 5 steps the player becomes thirsty
    // the player's thirsty functio will deduct 3 to 7 health points
    if (this->stepCounter == 5)
    {
        player->thirsty();
        //Reset the counter back to 0.
        this->stepCounter = 0;
    }
}

void Game::checkForCombat(Space*& currentSpace)
{
    // If there is a monster present in the room, engage fight with monster.
    if (currentSpace->hasMonster())
    {
        currentSpace->printDescription();

        Monster* monster = currentSpace->getMonster();
        cout << BOLDYELLOW << "\nThe " << monster->getName() << " moved to attack you!\n" << RESET;
        int choice = 1;
        while (choice == 1 && !player->isDead() && !monster->isDead())
        {
            cout << "\nQuick, Act now!\n"
                 << "1. Stay and fight\n"
                 << "2. Flee the area\n";
            player->printHP();
            choice = gameMenu.getInt(1,2);
            if (choice == 1)
            {
                int damage = player->attack(monster);
                monster->defend(damage);

                if (!monster->isDead())
                {
                    damage = monster->attack();
                    player->defend(damage);
                    cout << "\n";
                    if (!player->isDead())
                        currentSpace->printDescription();
                }
                else
                    this->hasVictory = true;
            }
            else if (choice == 2)
            {
                cout << YELLOW << "\nMoving to the south...\n" << RESET;
                currentSpace = currentSpace->getSouth();
                this->addStep();
            }
        }
    }
}
