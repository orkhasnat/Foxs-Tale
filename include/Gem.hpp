#ifndef GEM_H
#define GEM_H

#include "Item.hpp"

class Gem : public Item
{
    void setSprite(const int);

public:
    Gem(int);
    void bonus(int*);
};

#endif
