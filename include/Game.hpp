#ifndef GAME_H
#define GAME_H

#include <deque>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Spike.hpp"
#include "Ball.hpp"

class Ball;

class Game
{
private:
    int score, life, runspeed, slowdowntime;
    std::deque<Platform *> platforms;
    Ball *ball;
    sf::RectangleShape frame;
    sf::Music playing;
    friend void Coin::bonus(int *_score);
    friend void Gem::bonus(int *_life);
    friend void SlowDown::bonus(int *_runspeed);

    void newball();
    void newPlatform(PlatformType);
    void manageevents();
    void addPlatform();
    void levitate(const int);
    void draw() const;
    void rightarrow();
    void leftarrow();
    void pause();
    void burst();
    void fall();
    void bounce();
    void getBonus();

    inline void levelcheck(int temp)
    {
        if (score / 1000 > temp / 1000)
        {
            bg++;
            if (runspeed < 6)
                runspeed++;
        }
    }

    inline void drawscore() const
    {
        sf::Text text;
        text.setFont(arial);
        text.setString("Score: " + std::to_string(score));

        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setOutlineThickness(2);
        text.setOutlineColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        text.setPosition(800, 55);

        window.draw(text);
    }

    inline void drawremaining() const
    {
        sf::CircleShape circle[life];
        for (int i = 0; i < life; i++)
        {
            circle[i].setRadius(12);
            circle[i].setOutlineThickness(2);
            circle[i].setFillColor(sf::Color::Red);
            circle[i].setOutlineColor(sf::Color::Black);
            circle[i].setPosition(1200 - 30 * (i + 1), 65);
            window.draw(circle[i]);
        }
    }

public:
    Game();
    ~Game();
    void addScore(int);
    int getScore() const;
    void run();
};

#endif