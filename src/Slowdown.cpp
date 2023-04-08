#include "Slowdown.hpp"

SlowDown::SlowDown(int _x)
{
    setSprite(_x);
}

void SlowDown::setSprite(const int x)
{
    sf::Texture texture;
    texture.loadFromFile("../data/img/Platform.jpg");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setColor(sf::Color::Blue);
    sprite.setPosition(x, 680);
}

void SlowDown::bonus(int *slowdowntime)
{
    *slowdowntime+=19+(rand()&31);
}
