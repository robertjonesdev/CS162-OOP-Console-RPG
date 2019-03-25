/***************************************************************
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Character class implementation file
***************************************************************/
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Character.hpp"
#include "Monster.hpp"
#include "Item.hpp"
#include "Colors.hpp"
#include "Menu.hpp"

using namespace std;

/******************************************************************************
**  Constructor
*******************************************************************************/
Character::Character(std::string name, int hp)
{
    this->name = name;
    this->hp = hp;
    this->dead = false;
}

/******************************************************************************
** Destructor()
** Check for items in the character's inventory and delete those.
*******************************************************************************/
Character::~Character()
{
    //Delete inventory objects
    for (size_t i = 0; i < inventory.size(); i++)
    {
        delete inventory[i];
    }
}

/******************************************************************************
**  addItem()
** Setter for an item on the ground
*******************************************************************************/
bool Character::addItem(Item* item)
{
    if (inventory.size() == this->inventoryMax)
    {
        cout << BOLDRED << "Your inventory is full! Cannot add the item.\n" << RESET;
        return false;
    }
    else
    {
        inventory.push_back(item);
        cout << BOLDRED << "You picked up the " << item->getName() << " and added it to your inventory.\n" << RESET;
        return true;
    }
}

/******************************************************************************
**  removeItem()
** Getter for an item in the inventory so it can be passed back to the Room
*******************************************************************************/
Item* Character::removeItem()
{
    if (inventory.empty())
    {
        cout << BOLDRED << "Your inventory is empty!\n" << RESET;
        return nullptr;
    }
    else
    {
        cout << "\nSelect the item to remove\n";

        for (size_t i = 0; i < inventory.size(); i++)
        {
            cout << i+1 << ". " << inventory[i]->getName() << "\n";
        }
        cout << "Enter item number: ";
        Menu menu;
        int choice = menu.getInt(1, inventory.size());
        Item* tempItem = inventory[choice - 1];
        cout << BOLDRED << "You have dropped the " << tempItem->getName() << " on the ground.\n" << RESET;
        inventory.erase(inventory.begin() + (choice - 1));
        return tempItem;
    }
}

void Character::printHP()
{
    cout << "[HP=";
    if (getHP() <= 20)
        cout << BOLDRED;
    cout << getHP() << RESET << "]: ";
}


/******************************************************************************
**  printStatsAndInv()
** Print the name, health points, and iventory of the player.
*******************************************************************************/
void Character::printStatsAndInv()
{
    cout << "\n\tCharacter Stats\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    cout << left << setw(20) << "Name: " << name << "\n";
    cout << left << setw(20) << "Health Points: " << hp << "\n\n";
    if (inventory.empty())
    {
        cout << BOLDRED << "Your inventory is empty!\n" << RESET;
    }
    else
    {
        cout << "   Inventory (Limit 2 items)\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
        for (size_t i = 0; i < inventory.size(); i++)
        {
            cout << "Item " << i+1 << ": " <<inventory[i]->getName() << "\n";
        }
        cout << '\n';
    }
}

/******************************************************************************
**  usePotion()
** If the character has a potion in its inventory, it will use it. Health Points
** will be increased by 15 and the potion will dissapear.
*******************************************************************************/
void Character::usePotion()
{
    if (inventory.empty())
    {
        cout << BOLDRED << "You do not have the potion to use!\n" << RESET;
    }
    else
    {
        bool found = false;
        for (size_t i = 0; i < inventory.size(); i++)
        {
            if (inventory[i]->getType() == 3 && found == false)
            {
                cout << BLUE << "You drink the healing potion and feel much better! (+15 HP)\n" << RESET;
                //increase the character's health points by 15.
                this->hp += 15;
                //Remove it from inventory/game.
                found = true;
                delete inventory[i];
                inventory.erase(inventory.begin() + i);
            }
        }
        if (found == false)
        {
            cout << BOLDRED << "You do not have the potion to use!\n" << RESET;
        }
    }
}

/******************************************************************************
**  useKey()
** If the character has a key it will be passed back to the Game class in order
** to be passed to the Space to unlock a door.
*******************************************************************************/
Item* Character::useKey()
{
    if (inventory.empty())
    {
        cout << BOLDRED << "You do not have the key to use!\n" << RESET;
        return nullptr;
    }
    else
    {
        for (size_t i = 0; i < inventory.size(); i++)
        {
            if (inventory[i]->getType() == 1)
            {
                return inventory[i];
            }
        }
        cout << BOLDRED << "You do not have the key to use!\n" << RESET;
        return nullptr;
    }
}

/******************************************************************************
**  getHitMessage()
** This function is used for combat and changes depending on the weapon the
** character has. (longbow - arrows) (none - fists)
*******************************************************************************/
std::string Character::getHitMessage()
{
    for (size_t i = 0; i < inventory.size(); i++)
    {
        if (inventory[i]->getType() == 2)
        {
            //You shoot an arrow at the red dragon for 20 damage!
            return "shoot an arrow at";
        }
    }
    //You punch the red dragon for 5 damage!
    return "punch";
}

/******************************************************************************
**  getMissmessage()
** This function is used for combat and changes depending on the weapon the
** character has. (longbow - arrows) (none - fists)
*******************************************************************************/
std::string Character::getMissMessage()
{
    for (size_t i = 0; i < inventory.size(); i++)
    {
        if (inventory[i]->getType() == 2)
        {
            //You launch an arrow at the red dragon, but miss!
            return "launch an arrow at";
        }
    }
    //You swing at the red dragon, but miss!
    return "swing at";
}

/******************************************************************************
**  attack()
** This function is used for combat to calculate the damage inflicted on the mosnter.
*******************************************************************************/
int Character::attack(Monster* monster)
{
    int totalDamage = 0;
    int damage = 0;
    //default hit min/max for fists
    int hitMin = 1;
    int hitMax = 4;
    for (size_t i = 0; i < inventory.size(); i++)
    {
        if (inventory[i]->getType() == 2)
        {   // You have the longbow which increases your hits.
            hitMin = 3;
            hitMax = 10;
        }
    }
    int numAttacks = (rand() % 3) + 1;
    for (int i = 0; i < numAttacks; i++)
    {
        int attackType = (rand() % 10) + 1;
        if (attackType > 3) //60% chance of hit, 40% chance of miss.
        {
            //Hit
            damage = (rand() % (hitMax - hitMin + 1)) + hitMin;
            cout << BOLDRED << "You " << getHitMessage() << " the " << monster->getName() << " for " << damage << " damage!\n" << RESET;
            totalDamage += damage;
        }
        else if (attackType <= 3 && attackType > 1)
        {
            //Miss
            cout << CYAN << "You " << getMissMessage() << " the " << monster->getName() << " but miss!\n" << RESET;
        }
        else
        {
            cout << CYAN << "You lunge at the " << monster->getName() << "!\n" << RESET;
        }
    }
    return totalDamage;
}

/******************************************************************************
**  defend()
** This function is used for combat and assesses the damage the Monster inflects
** on the Character
*******************************************************************************/
void Character::defend(int hit)
{
    this->hp -= hit;
    if (this->hp <= 0)
    {
        this->dead = true;
    }
}

/******************************************************************************
**  thirsty()
** This function is called by the Game class when the stepCounter reaches 5
** The character will assess damage ranging from 3 to 7 and deduct it from
** Health Points.
*******************************************************************************/
void Character::thirsty()
{
    int damage = (rand() % (7 - 3 + 1)) + 3; // 3 to 7
    this->hp -= damage;
    cout << CYAN << "You feel a little thirsty. (-" << damage << " HP)\n" << RESET;
    if (this->hp <= 0)
    {
        this->dead = true;
    }
}
