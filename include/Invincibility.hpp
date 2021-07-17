#ifndef INVINCIBILITY_H
#define INVINCIBILITY_H

#include "Item.hpp"

class Invincibility : public Item
{
    void setSprite(const int);
public:
    Invincibility(int);
    void bonus(int*);
};

#endif