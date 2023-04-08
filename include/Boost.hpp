#ifndef BOOST_H
#define BOOST_H

#include "Item.hpp"

class Boost : public Item
{
    friend class Platform;
    void setSprite(const int);
    Boost(int);

public:
    void bonus(int*);
};

#endif
