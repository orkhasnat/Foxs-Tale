#ifndef PLATFORM_H
#define PLATFORM_H

#include "SFML/Graphics.hpp"
#include "Coin.hpp"
#include "Boost.hpp"
#include "Invincibility.hpp"
#include "Gem.hpp"
#include "Slowdown.hpp"
#include "misc.hpp"

class Platform
{
protected:
    int width;
    int ballx;
    Item *item;
    PlatformType platformtype;
    ItemType itemtype;
    sf::Texture texture;

public:
    sf::Sprite sprite;

    Platform(int, const ItemType);
    ~Platform();

    int getWidth() const;
    int getPlatformType() const;
    void setballx(int);
    int getballx() const;
    int getItemType() const;
    Item *getItem() const;
    void pickup();
    bool checkpickup() const;

    virtual void move()
    {
        sprite.move(0, -20);
        if (item)
            item->sprite.move(0, -20);
    }
};

#endif