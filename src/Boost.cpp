#include "Boost.hpp"

Boost::Boost(int _x)
{
    setSprite(_x);
}

void Boost::setSprite(const int x)
{
    sf::Texture texture;
    texture.loadFromFile("../data/img/Platform.jpg");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setColor(sf::Color::Magenta);
    sprite.setPosition(x, 680);
}

void Boost::bonus(int *isBoosted)
{
    *isBoosted+=19+(rand()&31);
}
