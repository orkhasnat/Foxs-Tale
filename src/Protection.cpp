#include "Protection.hpp"

Protection::Protection(int _x)
{
    setSprite(_x);
}

void Protection::setSprite(const int x)
{
    sf::Texture texture;
    texture.loadFromFile("data/img/Platform.jpg");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setColor(sf::Color::Green);
    sprite.setPosition(x, 680);
}

void Protection::bonus(int *_protection)
{
    *_protection+=19+(rand()&31);
}
