#ifndef PROTECTION_H
#define PROTECTION_H

#include "Item.hpp"

class Protection : public Item
{
    friend class Platform;
    void setSprite(const int);
    Protection(int);

public:
    void bonus(int*);
};

#endif
