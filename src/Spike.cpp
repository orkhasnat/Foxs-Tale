#include "Spike.hpp"

Spike::Spike(const int x) : Platform(x, nothing)
{
    platformtype = spike;

    sf::Texture texture;
    texture.loadFromFile("img/Platform.jpg");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, 10));
    sprite.setColor(sf::Color(150, 75, 0));
}