/***************************************************************
** Author:        Robert Jones
** Date:          March 19, 2019
** Description:   Item class defiition file.
***************************************************************/
#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item
{
private:
    int key;
    int type;
    std::string name;

public:
    Item(int, int, std::string);
    virtual ~Item() {};

    int getKey();
    int getType();
    std::string getName();
};

#endif //Item
