/***************************************************************
** Program name:  Final Project (CS162 Winter 2019)
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Locked Room class implementation file
***************************************************************/
#include <vector>
#include <iostream>
#include "LockedRoom.hpp"
#include "Menu.hpp"
#include "Colors.hpp"

using std::cout;

/******************************************************************************
**  Constructor
*******************************************************************************/
LockedRoom::LockedRoom(Space* north, Space* east, Space* south, Space* west)
    :Space(north, east, south, west)
{
    setLockedNorth();
}

/******************************************************************************
** Destructor()
** Check for items in the room's inventory and delete those.
*******************************************************************************/
LockedRoom::~LockedRoom()
{
    for (size_t i = 0; i < items.size(); i++)
        delete items[i];
}

/******************************************************************************
** Print Description()
** Provide a description of the room, any items there, and any exits.
*******************************************************************************/
void LockedRoom::printDescription()
{
    int exitcounter = 0;
    cout << BOLDCYAN << "\nDarkwood Forest\n" << RESET;
    cout << "   This narrow path is fairly plain, save for the small lanterns hanging from\n"
         << "the trees around. North of you lies a strangely large tree with what appears to\n"
         << "to be a door. The path leads east, west, and back south from here.\n";

    if (this->lockedNorth)
        cout << CYAN << "You notice a locked door to the north.\n" << RESET;

    if (items.size() > 0)
    {
        cout << CYAN << "You notice a ";
        for (size_t i = 0; i < items.size(); i++)
        {
            if (i > 0)
                cout << ", ";
            if (i > 0 && i == (items.size() - 1))
                cout << "and ";
            cout << items[i]->getName();
        }
        cout << " on the ground.\n" << RESET;
    }
    cout << BOLDGREEN << "Obvious exits: ";
    if (!this->lockedNorth && this->north != nullptr)
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
    cout << "\n" << RESET;
}

/******************************************************************************
**  setLockedNorth()
** To be called at the beginning of the game creation to the lock the door.
*******************************************************************************/
void LockedRoom::setLockedNorth() { this->lockedNorth = true; }

/******************************************************************************
**  UnlcoDoor()
** Takes the key item and checks to see if it is the correct key.
** if it is, then the door will unlcok.
*******************************************************************************/
void LockedRoom::unlockDoor(Item* item)
{
    if (item->getKey() == 101)
    {
        this->lockedNorth = false;
        cout << BOLDRED << "\nYou have unlocked the door to the north!\n" << RESET;
    }
    else
        cout << BOLDRED << "\nThis key does not unlock this door!\n" << RESET;
}

/******************************************************************************
**  roomIsLocked()
** Overriding function to tell the Game object that a room has a locked door.
*******************************************************************************/
bool LockedRoom::roomIsLocked()
{
    return this->lockedNorth;
}

/******************************************************************************
**  addItem()
** Setter for an item on the ground
*******************************************************************************/
void LockedRoom::addItem(Item* item) { items.push_back(item); }

/******************************************************************************
**  hasItem()
** OVerrides Space's virtual function to determine if the room has an item.
** Generally used for the displayMap function of the Game object.
*******************************************************************************/
bool LockedRoom::hasItem()
{
    if (items.size() > 0)
        return true;
    else
        return false;
}


/******************************************************************************
**  takeItem()
** Getter for an item on the ground
*******************************************************************************/
Item* LockedRoom::takeItem()
{
    if (items.size () == 1)
    {
        Item* tempItem = items[0];
        items.erase(items.begin());
        return tempItem;
    }
    else if (items.size() > 1)
    {
        Menu menu;
        cout << "Select the item to pickup\n";
        for (size_t i = 0; i < items.size(); i++)
            cout << i + 1 << ": " << items[i]->getName() << "\n";

        cout << "Enter the item number: ";
        int choice = menu.getInt(1, items.size());

        Item* tempItem = items[choice - 1];
        items.erase(items.begin() + (choice - 1));
        return tempItem;
    }
    else
        return nullptr;
}
