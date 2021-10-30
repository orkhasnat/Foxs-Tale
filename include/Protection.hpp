#ifndef PROTECTION_H
#define PROTECTION_H

#include "Item.hpp"

class Protection : public Item
{
    friend class Platform;
    Protection(int);
    void setSprite(const int);

public:
    void bonus(int *);
};

#endif
