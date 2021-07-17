#ifndef BOOST_H
#define BOOST_H

#include "Item.hpp"

class Boost : public Item
{
    void setSprite(const int);

public:
    Boost(int);
    void bonus(int *);
};

#endif