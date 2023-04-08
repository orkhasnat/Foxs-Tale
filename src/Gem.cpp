#include "Gem.hpp"

Gem::Gem(int _x)
{
    setSprite(_x);
}

void Gem::setSprite(const int x)
{
    sf::Texture texture;
    texture.loadFromFile("../data/img/Platform.jpg");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setColor(sf::Color::Cyan);
    sprite.setPosition(x, 680);
}

void Gem::bonus(int *life)
{
    *life=std::min(*life+1, 6);
}
