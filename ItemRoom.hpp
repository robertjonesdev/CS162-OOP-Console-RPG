/***************************************************************
** Program name:  Final Project (CS162 Winter 2019)
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Item Room class definition file
***************************************************************/
#ifndef ITEMROOM_HPP
#define ITEMROOM_HPP

#include <vector>
#include "Space.hpp"
#include "Item.hpp"

class ItemRoom : public Space
{
private:
    std::vector <Item*> items;

public:
    ItemRoom(Space* north = nullptr, Space* east = nullptr, Space* south = nullptr, Space* west = nullptr);
    virtual ~ItemRoom();
    void printDescription();
    void addItem(Item*);
    Item* takeItem();
    bool hasItem();
};

#endif //ItemRoom
