#ifndef SLOWDOWN_H
#define SLOWDOWN_H

#include "Item.hpp"

class SlowDown : public Item
{
    void setSprite(const int);

public:
    SlowDown(int);
    void bonus(int *);
};

#endif