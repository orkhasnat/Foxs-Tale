#ifndef BALL_H
#define BALL_H

#include "Platform.hpp"
#include "Queue.hpp"
#include "SFML/Graphics.hpp"
#include "Game.hpp"

class Ball
{
    int isProtected, isBoosted;
    Platform* standingOn;
    friend class Game;
    friend void Boost::bonus(int *_isBoosted);
    friend void Protection::bonus(int *_isProtected);

public:
    sf::CircleShape circle;

    Ball(Platform*);
    bool isFalling() const;
    int findPlatform(Queue&);
};

#endif
