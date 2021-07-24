#include "Invincibility.hpp"

void Invincibility::setSprite(const int x)
{
    sf::Texture texture;
    texture.loadFromFile("data/img/Platform.jpg");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setColor(sf::Color::Green);
    sprite.setPosition(x, 680);
}

Invincibility::Invincibility(int _x)
{
    setSprite(_x);
}

void Invincibility::bonus(int *_slowdowntime)
{
    *_slowdowntime += 19 + (rand() & 31);
}