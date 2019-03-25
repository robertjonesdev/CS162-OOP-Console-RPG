/***************************************************************
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Moster Room class definition file
***************************************************************/
#ifndef MONSTERROOM_HPP
#define MONSTERROOM_HPP

#include <vector>
#include "Space.hpp"
#include "Item.hpp"
#include "Monster.hpp"
#include "Character.hpp"

class MonsterRoom : public Space
{
private:
    Monster* monster = nullptr;

public:
    MonsterRoom(Space* north = nullptr, Space* east = nullptr, Space* south = nullptr, Space* west = nullptr);
    virtual ~MonsterRoom();

    void printDescription();
    void addMonster(Monster*);
    Monster* getMonster();
    void removeMonster();
    bool hasMonster();
};

#endif //ItemRoom
