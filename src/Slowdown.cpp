#include "Slowdown.hpp"

void SlowDown::setSprite(const int x)
{
    sf::Texture texture;
    texture.loadFromFile("img/Platform.jpg");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setColor(sf::Color::Blue);
    sprite.setPosition(x, 680);
}

SlowDown::SlowDown(int _x)
{
    setSprite(_x);
}

void SlowDown::bonus(int *_slowdowntime)
{
    *_slowdowntime += 19 + (rand() & 31);
}
