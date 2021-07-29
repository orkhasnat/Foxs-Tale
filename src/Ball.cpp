#include "Ball.hpp"

Ball::Ball(Platform* platform): standingOn(platform), isProtected(0), isBoosted(0)
{
    circle.setRadius(7);
    circle.setOutlineThickness(1);
    circle.setFillColor(sf::Color::Red);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOrigin(circle.getRadius(), 2*circle.getRadius()+circle.getOutlineThickness());
    platform->setballx(platform->sprite.getPosition().x + platform->getWidth()/2 + (1-2*(rand()&1))*(rand()%(platform->getWidth()/2-5)));
    circle.setPosition(platform->sprite.getPosition().x+platform->getballx(), platform->sprite.getPosition().y);
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
        if(circle.getPosition().y >= platforms[i]->sprite.getPosition().y && circle.getPosition().y <= platforms[i]->sprite.getPosition().y+11)
            if(circle.getPosition().x+circle.getRadius() > platforms[i]->sprite.getPosition().x)
                if(circle.getPosition().x-circle.getRadius() < platforms[i]->sprite.getPosition().x+platforms[i]->getWidth())
                {
                    if(platforms[i]->getPlatformType()==spike || platforms[i]->getPlatformType()==movingspike) return 3*(!isProtected);
                    if(platforms[i]->getPlatformType()==bouncing) return 4;
                    standingOn=platforms[i];
                    platforms[i]->setballx(circle.getPosition().x);
                    if(platforms[i]->checkpickup()) return 2;
                    return 1;
                }
    }

    return 0;
}
