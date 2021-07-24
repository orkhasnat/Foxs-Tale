#include "Coin.hpp"

void Coin::setSprite(const int x)
{
    sf::Texture texture;
    texture.loadFromFile("data/img/Platform.jpg");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
    sprite.setColor(sf::Color::Yellow);
    sprite.setPosition(x, 680);
}
Coin::Coin(int _x)
{
    setSprite(_x);
}

void Coin::bonus(int *_score)
{
    *_score += 100 + rand() % 200;
}