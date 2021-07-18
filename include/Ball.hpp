#ifndef BALL_H
#define BALL_H

#include <deque>
#include "Platform.hpp"
#include "SFML/Graphics.hpp"
#include "Game.hpp"

class Ball
{
    int isBouncing, isProtected, isBoosted;
    Platform *standingOn;
    friend class Game;
    friend void Boost::bonus(int *_isBoosted);
    friend void Invincibility::bonus(int *_isProtected);

public:
    sf::CircleShape circle;

    Ball(Platform *);
    bool isFalling() const;
    int findPlatform(std::deque<Platform *>);
};

#endif