/***************************************************************
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Character class definition file
***************************************************************/
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>
#include <string>
#include "Item.hpp"
#include "Monster.hpp"

class Character
{
private:
    std::vector<Item*> inventory;
    const int inventoryMax = 2;
    std::string name;
    int hp;
    bool dead;

public:
    Character(std::string, int);
    virtual ~Character();

    int getHP() { return this->hp; };
    bool isDead() { return this->dead; };
    bool addItem(Item*);
    Item* removeItem();
    void printHP();
    void printStatsAndInv();
    void usePotion();
    Item* useKey();
    std::string getHitMessage();
    std::string getMissMessage();
    int attack(Monster*);
    void defend(int);
    void thirsty();
};

#endif //Character
