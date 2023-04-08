#ifndef SLOWDOWN_H
#define SLOWDOWN_H

#include "Item.hpp"

class SlowDown : public Item
{
    friend class Platform;
    void setSprite(const int);
    SlowDown(int);

public:
    void bonus(int*);
};

#endif
