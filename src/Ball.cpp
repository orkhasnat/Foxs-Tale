#include "Ball.hpp"

Ball::Ball(Platform* platform): standingOn(platform), isProtected(0), isBoosted(0), direction(1)
{
    // circle.setRadius(7);
    // circle.setOutlineThickness(1);
    // circle.setFillColor(sf::Color::Red);
    // circle.setOutlineColor(sf::Color::Black);
    // circle.setOrigin(circle.getRadius(), 2*circle.getRadius()+circle.getOutlineThickness());
    texture.loadFromFile("data/img/running.png");
    fox.setTexture(texture);
    fox.setTextureRect(sf::IntRect(0, 0, 108, 108));
    platform->setballx(platform->sprite.getPosition().x + platform->getWidth()/2 + (1-2*(rand()&1))*(rand()%(platform->getWidth()/2-5)));
    fox.setOrigin(54, 80);
    fox.setScale(0.5, 0.5);
    fox.setPosition(platform->sprite.getPosition().x+platform->getballx(), platform->sprite.getPosition().y);
}

bool Ball::isFalling() const
{
    return !standingOn;
}

int Ball::findPlatform(Queue& platforms)
{
    standingOn=nullptr;

    for(int i=0; i<platforms.size(); i++)
    {
        if(fox.getPosition().y >= platforms[i]->sprite.getPosition().y && fox.getPosition().y <= platforms[i]->sprite.getPosition().y+11)
            if(fox.getPosition().x+7> platforms[i]->sprite.getPosition().x)
                if(fox.getPosition().x-7 < platforms[i]->sprite.getPosition().x+platforms[i]->getWidth())
                {
                    if(platforms[i]->getPlatformType()==spike || platforms[i]->getPlatformType()==movingspike) return 3*(!isProtected);
                    if(platforms[i]->getPlatformType()==bouncing) return 4;
                    standingOn=platforms[i];
                    platforms[i]->setballx(fox.getPosition().x);
                    if(platforms[i]->checkpickup()) return 2;
                    return 1;
                }
    }

    return 0;
}
