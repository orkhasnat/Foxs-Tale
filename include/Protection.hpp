#ifndef PROTECTION_H
#define PROTECTION_H

#include "Item.hpp"

class Protection : public Item
{
    void setSprite(const int);
public:
    Protection(int);
    void bonus(int*);
};

#endif
