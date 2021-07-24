#ifndef ITEM_H
#define ITEM_H

#include "SFML/Graphics.hpp"

class Item
{
protected:
    virtual void setSprite(const int x) = 0;

public:
    sf::Sprite sprite;
    virtual void bonus(int *stat) = 0;
};

#endif