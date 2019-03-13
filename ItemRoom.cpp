/***************************************************************
** Program name:  Final Project (CS162 Winter 2019)
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Item Room class implementation file
***************************************************************/
#include <iostream>
#include <vector>
#include "ItemRoom.hpp"
#include "Menu.hpp"
#include "Colors.hpp"

using std::cout;

/******************************************************************************
** Constructor()
*******************************************************************************/
ItemRoom::ItemRoom(Space* north, Space* east, Space* south, Space* west)
    :Space(north, east, south, west) {}

/******************************************************************************
** Destructor()
** Check for items in the room's inventory and delete those.
*******************************************************************************/
ItemRoom::~ItemRoom()
{
    for (size_t i = 0; i < items.size(); i++)
        delete items[i];
}

/******************************************************************************
** Print Description()
** Provide a description of the room, any items there, and any exits.
*******************************************************************************/
void ItemRoom::printDescription()
{
    int exitcounter = 0;
    cout << BOLDCYAN << "\nDarkwood Forest\n" << RESET;
    cout << "   The trees become very thick around you now, and you can barely see where\n"
         << "you're going due to the only light source being from the village to the south and\n"
         << "the light shining through the trees. You hear the sound of rippling water south\n"
         << "of here.\n";

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
**  addItem()
** Setter for an item on the ground
*******************************************************************************/
void ItemRoom::addItem(Item* item) { items.push_back(item); }


/******************************************************************************
**  hasItem()
** OVerrides Space's virtual function to determine if the room has an item.
** Generally used for the displayMap function of the Game object.
*******************************************************************************/
bool ItemRoom::hasItem()
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
Item* ItemRoom::takeItem()
{
    if (items.size() > 1)
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
    else if (items.size () == 1)
    {
        Item* tempItem = items[0];
        items.erase(items.begin());
        return tempItem;
    }
    else
        return nullptr;
}
