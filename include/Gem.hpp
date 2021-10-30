#ifndef GEM_H
#define GEM_H

#include "Item.hpp"

class Gem : public Item
{
    friend class Platform;
    Gem(int);
    void setSprite(const int);

public:
    void bonus(int *);
};

#endif
