/***************************************************************
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Monster class implementation file
***************************************************************/
#include <string>
#include <iostream>
#include "Monster.hpp"
#include "Colors.hpp"

using std::cout;

/******************************************************************************
**  Constructor
*******************************************************************************/
Monster::Monster(std::string name, int hp)
{
    this->name = name;
    this->hp = hp;
    this->dead = false;
}

/******************************************************************************
**  attack()
** This function is used for combat to calculate the damage inflicted by the
** monster on to the Character. It is passed back to the Game object as an integer
** and the Game object will then pass the damage to the Character's defend function.
*******************************************************************************/
int Monster::attack()
{
    int totalDamage = 0;
    int damage = 0;
    int hitMin = 2;
    int hitMax = 7;

    int numAttacks = (rand() % 3) + 1;
    for (int i = 0; i < numAttacks; i++)
    {
        int attackType = (rand() % 10) + 1;
        if (attackType > 7) //60% chance of hit, 40% chance of miss.
        {
            //Hit
            damage = (rand() % (hitMax - hitMin + 1)) + hitMin;
            cout << BOLDRED << "The " << getName() << " breathes dragonfire on you for " << damage << " damage!\n" << RESET;
            totalDamage += damage;
        }
        else if (attackType <= 7 && attackType > 3)
        {
            //Hit
            damage = (rand() % (hitMax - hitMin + 1)) + hitMin;
            cout << BOLDRED << "The " << getName() << " rips you with her talons for " << damage << " damage!\n" << RESET;
            totalDamage += damage;
        }
        else if (attackType <= 3 && attackType > 1) //Miss
            cout << CYAN << "The " << getName() << " swipes at you with her talons!\n" << RESET;
        else // Also miss
            cout << CYAN << "The " << getName() << " snaps at you with her fangs!\n" << RESET;
    }
    return totalDamage;
}

/******************************************************************************
**  defend()
** This function is used for combat and assesses the damage the Character inflects
** on the Monster
*******************************************************************************/
void Monster::defend(int hit)
{
    this->hp -= hit;
    if (this->hp <= 0)
    {
        cout << YELLOW << "The " << getName() << " squeals piercingly, and collapses!\n" << RESET;
        this->dead = true;
    }
}
