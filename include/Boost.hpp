#ifndef BOOST_H
#define BOOST_H

#include "Item.hpp"

class Boost : public Item
{
    friend class Platform;
    Boost(int);
    void setSprite(const int);

public:
    void bonus(int *);
};

#endif
