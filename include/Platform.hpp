#ifndef PLATFORM_H
#define PLATFORM_H

#include "SFML/Graphics.hpp"
#include "Coin.hpp"
#include "Boost.hpp"
#include "Protection.hpp"
#include "Gem.hpp"
#include "Slowdown.hpp"
#include "misc.hpp"

class Platform
{
protected:
    int width, ballx;
    Item *item;
    PlatformType platformtype;
    ItemType itemtype;
    sf::Texture texture;

public:
    sf::Sprite sprite;

    Platform(int, const ItemType);
    ~Platform();

    int getWidth() const;
    void setballx(int);
    int getballx() const;
    Item* getItem() const;
    int getItemType() const;
    int getPlatformType() const;
    bool checkpickup() const;
    void pickup();

    virtual void move()
    {
        sprite.move(0, -20);
        if(item) item->sprite.move(0, -20);
    }
};

#endif
