#ifndef COIN_H
#define COIN_H

#include "Item.hpp"

class Coin : public Item
{
    friend class Platform;
    Coin(int);
    void setSprite(const int);

public:
    void bonus(int *);
};

#endif