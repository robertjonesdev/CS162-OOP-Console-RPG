/*********************************************************************
** Program name:  Final Project CS 162-400, Winter 2019
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:   Menu.hpp, Menu Class Definition
*********************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <map>
#include <string>

using namespace std;

class Menu
{
    private:
        bool quit;
        string menuTitle;
        vector<std::string> menuList;
        std::map<string, int> commands;

    public:
        //Constructors and Deconstructor
        Menu();
        Menu(string menuTitle, vector<string> menuList);
        virtual ~Menu();

        //Accessors
        bool getQuit();

        //Modifiers
        void addOption(string strOption);
        void rmOption(int option);
        void changeTitle(string strTitle);
        void setQuit();

        //Functions
        void printMenu();
        void printBorder(const int&, const char&)const;
        int getChoice();
        int getInt(int min, int max);
        double getDouble(double min, double max);
        std::string getString();
        int getCommand();
        void getEnter()const;
        void clearScreen()const;
};

#endif
