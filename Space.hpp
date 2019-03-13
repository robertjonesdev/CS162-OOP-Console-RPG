/*******************************************************************************
** Program name: Final Project - A Text-based Game (CS162 Winter 2019)
** Author:       Robert Jones
** Date:         March 19, 2019
** Description: Space class definitio file. Abstract class
**               is inherited by ItemRoom, LockedRoom, and MonsterRoom
***************************************************************/
#ifndef SPACE_HPP
#define SPACE_HPP

#include "Item.hpp"
#include "Monster.hpp"

class Space
{
    protected:
        Space* north;
        Space* east;
        Space* south;
        Space* west;

    public:
        //Constructor & Destructor
        Space(Space* top = nullptr, Space* right = nullptr, Space* bottom = nullptr, Space* left = nullptr);
        virtual ~Space() {};

        virtual void setLockedNorth() {};
        virtual void addItem(Item*) {};
        virtual Item* takeItem() { return nullptr; };
        virtual void addMonster(Monster*) {};
        virtual Monster* getMonster() { return nullptr; };
        virtual void unlockDoor(Item*) {};
        virtual bool roomIsLocked() {  return false; };
        virtual bool hasItem() { return false; };
        virtual bool hasMonster() { return false; };

        void setNorth(Space*);
        void setEast(Space*);
        void setSouth(Space*);
        void setWest(Space*);

        Space* getNorth();
        Space* getEast();
        Space* getSouth();
        Space* getWest();

        virtual void printDescription() = 0;
};
#endif //Space
