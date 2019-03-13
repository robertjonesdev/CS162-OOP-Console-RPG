/***************************************************************
** Program name:  Final Project (CS162 Winter 2019)
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:   Item class implementation file.
***************************************************************/
#include "Item.hpp"
#include <string>

using std::string;
// Types
// 1 = Door key
// 2 = Weapon
// 3 = Healing Potion

/******************************************************************************
**  Constructor
*******************************************************************************/
Item::Item(int key, int type, std::string name)
{
    this->key = key;
    this->type = type;
    this->name = name;
}

/******************************************************************************
**  Getters & Setters
*******************************************************************************/
int Item::getKey() { return this->key; }

int Item::getType() { return this->type; }

std::string Item::getName() { return this->name; }
