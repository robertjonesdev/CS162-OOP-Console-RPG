/***************************************************************
** Program name:  Final Project (CS162 Winter 2019)
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Locked Room class definition file
***************************************************************/
#ifndef LOCKEDROOM_HPP
#define LOCKEDROOM_HPP

#include <vector>
#include "Space.hpp"
#include "Item.hpp"

class LockedRoom : public Space
{
private:
    bool lockedNorth = false;
    Space* lockedRoom = nullptr;
    std::vector <Item*> items;

public:
    LockedRoom(Space* north = nullptr, Space* east = nullptr, Space* south = nullptr, Space* west = nullptr);
    virtual ~LockedRoom();

    void printDescription();
    void setLockedNorth();
    void unlockDoor(Item*);
    bool roomIsLocked();
    void addItem(Item*);
    Item* takeItem();
    bool hasItem();
};

#endif //LockedRoom
