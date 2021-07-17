#include "Boost.hpp"

void Boost::setSprite(const int x)
{
    sf::Texture texture;
    texture.loadFromFile("img/Platform.jpg");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setColor(sf::Color::Magenta);
    sprite.setPosition(x, 680);
}

Boost::Boost(int _x)
{
    setSprite(_x);
}

void Boost::bonus(int *_isBoosted)
{
    *_isBoosted += 19 + (rand() & 31);
}