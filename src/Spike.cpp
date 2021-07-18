#include "Spike.hpp"

Spike::Spike(int x) : Platform(x, nothing)
{
    platformtype = spike;
    width=width/8*8;
    
    texture.loadFromFile("data/img/Spike.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, 10));
    //sprite.setColor(sf::Color(150, 75, 0));
}