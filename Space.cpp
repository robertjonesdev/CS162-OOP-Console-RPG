/***************************************************************
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Space class implementation file
**               This is an abstract class with a pure virtual function.
**               ItemRoom, LockedRoom, and MonsterRoom inherit from this class.
***************************************************************/
#include "Space.hpp"
/******************************************************************************
** Constructor()
** This takes as arguments pointers to other Spaces in each direction.
** At construction it will become part of the 2-D Linked List.
*******************************************************************************/
Space::Space(Space* north, Space* east, Space* south, Space* west)
{
    this->north = north;
    this->east = east;
    this->south = south;
    this->west = west;
}

/******************************************************************************
** Getters & Setters
** Return or Set Pointers to other Spaces
*******************************************************************************/
void Space::setNorth(Space* tempSpace) { this->north = tempSpace; }

void Space::setEast(Space* tempSpace) { this->east = tempSpace; }

void Space::setWest(Space* tempSpace) { this->west = tempSpace; }

void Space::setSouth(Space* tempSpace) { this->south = tempSpace; }

Space* Space::getNorth() { return this->north; }

Space* Space::getEast() { return this->east; }

Space* Space::getWest() { return this->west; }

Space* Space::getSouth() { return this->south; }
