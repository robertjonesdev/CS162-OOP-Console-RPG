/*******************************************************************************
** Program name: OOP Console RPG - Myrddin Emrys Realm
** Author:       Robert Jones
** Date:         March 19, 2019
** Description:  “Myrddin Emry’s Realm” is a one-player, text-based fantasy game
 using object-oriented programming concepts. The character, Myrddin Emrys, starts
 just to the north of Town in the Darkwood Forest. The player can move north,
 south, east or west depending on the available path through the forest. Myrddin
 will encounter locked doors, items, healing potions, and eventually a Red Dragon.
 Myrddin can fight with either his fists or with the use of a longbow to shoot
 arrows.
*******************************************************************************/

#include <ctime>          //Random
#include "Menu.hpp"
#include "Game.hpp"

int main()
{
    //Seed the random function for the Dice class.
    srand(time(NULL));

    //Create the pre-game enter/exit menu.
    vector<string> menuList;
    menuList.push_back("Enter the Realm.");
    Menu menu("", menuList);

    //Loop the menu until user quits.
    while (!menu.getQuit())
    {
        menu.clearScreen();
        menu.printMenu();

        switch (menu.getChoice())
        {
            case 1:
            {   //Create game instance and play game.
                Game myGame;
                break;
            }
        }
    }
    return 0;
}
