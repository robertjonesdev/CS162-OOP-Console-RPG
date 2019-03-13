/***************************************************************
** Program name:  Final Project (CS162 Winter 2019)
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Monster class definition file
***************************************************************/
#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>

class Monster
{
private:
    std::string name;
    int hp;
    bool dead;

public:
    Monster(std::string, int);
    virtual ~Monster() {};
    std::string getName() { return this->name; };
    bool isDead() { return this->dead; };
    int attack();
    void defend(int);
};

#endif //Monster
