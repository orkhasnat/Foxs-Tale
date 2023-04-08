#include "BouncyPlatform.hpp"

BouncyPlatform::BouncyPlatform(int x): Platform(x, nothing)
{
    platformtype=bouncing;
    texture.loadFromFile("../data/img/Platform.jpg");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, 10));
    sprite.setColor(sf::Color(255, 120, 31));
}
