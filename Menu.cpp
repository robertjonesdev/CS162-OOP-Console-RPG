/*********************************************************************
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:   Menu.cpp Menu class implementation
**                Includes input validation.
*********************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Menu.hpp"
#include "Colors.hpp"

//Constructors & Deconstructor
Menu::Menu()
{
    this->quit = false;

    commands.insert(make_pair("north", 1));
    commands.insert(make_pair("n", 1));
    commands.insert(make_pair("east", 2));
    commands.insert(make_pair("e", 2));
    commands.insert(make_pair("south", 3));
    commands.insert(make_pair("s", 3));
    commands.insert(make_pair("west", 4));
    commands.insert(make_pair("w", 4));
    commands.insert(make_pair("get", 5));
    commands.insert(make_pair("g", 5));
    commands.insert(make_pair("drop", 6));
    commands.insert(make_pair("d", 6));
    commands.insert(make_pair("unlock", 7));
    commands.insert(make_pair("u", 7));
    commands.insert(make_pair("drink", 8));
    commands.insert(make_pair("dr", 8));
    commands.insert(make_pair("stats", 9));
    commands.insert(make_pair("help", 10));
    commands.insert(make_pair("?", 10));
    commands.insert(make_pair("quit", 11));
    commands.insert(make_pair("exit", 11));
    commands.insert(make_pair("q", 11));
}

Menu::Menu(std::string strTitle, std::vector<std::string> vecList)
{
    this->menuTitle = strTitle;
    this->menuList = vecList;
    this->quit = false;
}

Menu::~Menu() { }

//Accessors
bool Menu::getQuit()
{
    return this->quit;
}

//Modifiers
void Menu::addOption(std::string strOption)
{
    this->menuList.push_back(strOption);
}

void Menu::rmOption(int option)
{
    this->menuList.erase(this->menuList.begin() + option - 1);
}

void Menu::changeTitle(std::string strTitle)
{
    this->menuTitle = strTitle;
}

void Menu::setQuit()
{
    this->quit = true;
}

//Functions
void Menu::printMenu()
{

    std::cout << BOLDGREEN;
    std::ifstream graphic("graphic.txt");
    std::string line;
    while ( getline(graphic, line) )
    std::cout << line << std::endl;
    graphic.close();
    std::cout << RESET;
    std::cout << GREEN << "\n   Who knows what monstrous creatures lurk in Darkwood forest?\n\n" << RESET
                 << "   Only the foolhardy would risk an encounter with the unknown\n"
                 << "perils that lurk in the murky depths of Darkwood Forest. Yet there\n"
                 << "is no alternative, for your quest is a desperate race against time\n"
                 << "to find Yaztromo's Tower and defeat the dragon that keeps your fellow\n"
                 << "countrymen in prison.\n"
                 << "   Make your way through the Darkwood Forest now. Along the way you\n"
                 << "will find weapons, items, and healing potions to assist you in your\n"
                 << "journey. You must act quickly, lest you become too thirsty and hungry\n"
                 << "to continue.\n\n";
    for (int i = 1; i <= this->menuList.size(); i++)
    {
      std::cout << i << ". " << this->menuList[i-1] << '\n';
    }
    std::cout << (this->menuList.size() + 1) << ". Exit the Game\n";
}

void Menu::printBorder(const int& length, const char& fill)const
{
    std::cout << '\n';
    std::cout.width(length);
    std::cout.fill(fill);
    std::cout << fill << std::endl;
    std::cout.fill(' ');
}

int Menu::getChoice()
{
    //SOURCE CITATION: Adapted from the following tutorial:
    //Lesson 17: Data validation / Type checking with StringStream
    //http://beginnerscpp.com/lesson-17-data-validation-type-checking-with-stringstream/
    std::cout << "Enter choice: ";
    std::string strInput = "";
    int choice = 0;
    bool isValid = false;
    while (!isValid)
    {
        getline(std::cin, strInput);
        std::stringstream ss(strInput);
        if (strInput.find_first_not_of("0123456789") == string::npos && ss >> choice //Implemented from Piazza post #254
            && choice >= 1 && choice <= (this->menuList.size() + 1))
        {
            isValid = true;
        }
        else
        {
            std::cout << "\nInvalid input. Re-enter choice: ";
        }
    }
    if (choice == this->menuList.size()+1)
    {
        this->quit = true;
    }
    return choice;
}

int Menu::getInt(int min, int max)
{
    //SOURCE CITATION: Adapted from the following tutorial:
    //Lesson 17: Data validation / Type checking with StringStream
    //http://beginnerscpp.com/lesson-17-data-validation-type-checking-with-stringstream/
    std::string strInput = "";
    int choice = 0;
    bool isValid = false;
    while (!isValid)
    {
        getline(std::cin, strInput);
        std::stringstream ss(strInput);
        if (((strInput.find_first_not_of("0123456789") == string::npos) //Implemented from Piazza post #254
            || (strInput.substr(0, 1) == "-" && (strInput.find_first_not_of("0123456789", 1) == string::npos))) //Account fo rnegative integers
            && ss >> choice && choice >= min && choice <= max)
        {
            isValid = true;
        }
        else
        {
           std::cout << "\nInvalid input. Re-enter choice (" << min << " - " << max << "): ";
        }
    }
    return choice;
}

double Menu::getDouble(double min, double max)
{
    //SOURCE CITATION: Adapted from the following tutorial:
    //Lesson 17: Data validation / Type checking with StringStream
    //http://beginnerscpp.com/lesson-17-data-validation-type-checking-with-stringstream/
    std::string strInput = "";
    double input = 0;
    bool isValid = false;
    while (!isValid)
    {
        getline(std::cin, strInput);
        std::stringstream ss(strInput);
        if (((strInput.find_first_not_of("0123456789.") == string::npos && std::count(strInput.begin(), strInput.end(), '.') <= 1) //Implemented from Piazza post #254
            || (strInput.substr(0, 1) == "-" && (strInput.find_first_not_of("0123456789.", 1) == string::npos)
            && std::count(strInput.begin(), strInput.end(), '.') <= 1)) //Account for rnegative integers
            && ss >> input && input >= min && input <= max)
        {
            isValid = true;
        }
        else
        {
            std::cout << "\nInvalid input. Re-enter choice (" << min << " - " << max << "): ";
        }
    }
    return input;
}

std::string Menu::getString()
{
    std::string strInput = "";
    bool isValid = false;
    while (!isValid)
    {
        getline(std::cin, strInput);
        std::stringstream ss(strInput);
        if (ss.str() != "")
        {
            isValid = true;
            return ss.str();
        }
        else
        {
            std::cout << "\nInvalid input. Re-enter string: ";
        }
    }
}

int Menu::getCommand()
{
    std::string strInput;
    getline(std::cin, strInput);
    auto search = commands.find(strInput);
    if (search != commands.end())
    {
        return search->second;
    }
    else
    {
        std::cout << GREEN << "You say \"" << strInput << "\"\n" << RESET;
        std::cout << "Type \"?\" for help.\n";
        return 99;
    }
}

void Menu::getEnter()const
{
    std::cout << BOLDCYAN << "\nPress ENTER to continue..." << RESET;
    std::cin.get();

}

void Menu::clearScreen()const
{
    #ifdef _WIN32
		std::system("cls");
	#else
		//Assume POSIX
		std::cout << "\033[2J\033[1;1H";
	#endif
}
