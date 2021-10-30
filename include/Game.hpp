#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Queue.hpp"
#include "Ball.hpp"
#include "Platform.hpp"
#include "Spike.hpp"
#include "MovingPlatform.hpp"
#include "BouncyPlatform.hpp"

class Ball;

class Game
{
private:
    int score, life, runspeed, slowdowntime;
    Queue<Platform*> platforms;
    Ball *ball;
    sf::Texture texture, boostedTexture;
    sf::Sprite spikes;
    sf::Music playing;
    friend void Coin::bonus(int *_score);
    friend void Gem::bonus(int *_life);
    friend void SlowDown::bonus(int *_runspeed);

    void newball();
    void newPlatform(PlatformType);
    void addPlatform();
    void manageevents();
    void pause();
    void levelcheck(int);
    void drawscore() const;
    void drawremaining() const;
    void draw();
    void levitate(const int);
    void leftarrow();
    void rightarrow();
    void fall();
    void bounce();
    void getBonus();
    void burst();

public:
    Game();
    ~Game();
    int X = 0, Y = 0;

    void addScore(int);
    int getScore() const;
    void run();

    class Not_Enough_Platforms{};
};

#endif
