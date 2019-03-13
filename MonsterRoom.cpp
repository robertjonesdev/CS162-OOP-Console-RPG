/***************************************************************
** Program name:  Final Project (CS162 Winter 2019)
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:   Monster Room class implementation file
***************************************************************/
#include <iostream>
#include <vector>
#include "MonsterRoom.hpp"
#include "Colors.hpp"

using std::cout;

/******************************************************************************
**  Constructor
*******************************************************************************/
MonsterRoom::MonsterRoom(Space* north, Space* east, Space* south, Space* west)
    :Space(north, east, south, west) {}

/******************************************************************************
** Destructor()
** Check for monsters in the room and deletes their allocated memory..
*******************************************************************************/
MonsterRoom::~MonsterRoom() { delete monster; }

/******************************************************************************
** Print Description()
** Provide a description of the room, any items there, and any exits.
*******************************************************************************/
void MonsterRoom::printDescription()
{
    int exitcounter = 0;
    cout << BOLDCYAN << "\nYaztromo's Tower\n" << RESET;
    cout << "   Yaztromo's Tower is where Gereth Yaztromo, the most famous wizard of Allansia\n"
         << "and his familiar guardian dragon live. It is situated on the northern fringes\n"
         << "of the Darwood Forest. The Tower is magically protected from intruders and stores\n"
         << "a precious library full of magic scrolls and other trinkets. Notable is also \n"
         << "the telescope peering from the glass dome on north of the Tower.\n";
    if (this->monster != nullptr)
    {
        cout << MAGENTA << "Also here: " << BOLDMAGENTA << this->monster->getName() << ".\n" << RESET;
    }
    cout << BOLDGREEN << "Obvious exits: ";
    if (this->north != nullptr)
    {
        cout << "north";
        exitcounter++;
    }
    if (this->east != nullptr)
    {
        if (exitcounter > 0)
            cout << ", ";
        cout << "east";
        exitcounter++;
    }
    if (this->west != nullptr)
    {
        if (exitcounter > 0)
            cout << ", ";
        cout << "west";
        exitcounter++;
    }
    if (this->south != nullptr)
    {
        if (exitcounter > 0)
            cout << ", ";
        cout << "south";
        exitcounter++;
    }
    cout << RESET << "\n";
}

/******************************************************************************
**  addMonster()
** Setter for monster object in the room
*******************************************************************************/
void MonsterRoom::addMonster(Monster* monster) { this->monster = monster; }

/******************************************************************************
**  getMonster()
** Getter for a monster in the room.
*******************************************************************************/
Monster* MonsterRoom::getMonster() { return this->monster; }

/******************************************************************************
**  hasMonster()
** Returns true/false if a monster is present
*******************************************************************************/
bool MonsterRoom::hasMonster()
{
    if (this->monster != nullptr)
        return true;
    else
        return false;
}


/******************************************************************************
**  removeMonster()
** Deletes monster object.
*******************************************************************************/
void MonsterRoom::removeMonster()
{
    delete this->monster;
    this->monster = nullptr;
}
