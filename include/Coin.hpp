#ifndef COIN_H
#define COIN_H

#include "Item.hpp"

class Coin : public Item
{
    void setSprite(const int);
public:
    Coin(int);
    void bonus(int*);
};

#endif