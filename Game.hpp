/***************************************************************
** Program name:  Final Project (CS162 Winter 2019)
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:  Game class definition file
***************************************************************/
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <map>
#include "Menu.hpp"
#include "Character.hpp"
#include "Monster.hpp"
#include "Space.hpp"

using namespace std;

class Game
{
    private:
        vector< vector<Space*> > gameMap{11,vector<Space*>()};
        Menu gameMenu;
        int stepCounter;
        bool hasVictory;
        Space* startingSpace;
        Character* player;
        void createMap();
        void playGame();
        void printMap(Space* currentSpace);
        void printMenu();
        void addStep();
        void checkForCombat(Space*&);

    public:
        Game();
        virtual ~Game();

};
#endif //Game
