#ifndef COIN_H
#define COIN_H

#include "Item.hpp"

class Coin : public Item
{
    friend class Platform;
    void setSprite(const int);
    Coin(int);

public:
    void bonus(int*);
};

#endif
