#include "Spike.hpp"

Spike::Spike(int x) : Platform(x, nothing)
{
    platformtype=spike;
    width=width/8*8;

    texture.loadFromFile("data/img/Spikes.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, 10));
}
