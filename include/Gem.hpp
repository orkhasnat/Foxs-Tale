#ifndef GEM_H
#define GEM_H

#include "Item.hpp"

class Gem : public Item
{
    friend class Platform;
    void setSprite(const int);
    Gem(int);

public:
    void bonus(int*);
};

#endif
