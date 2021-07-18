#ifndef MISC_H
#define MISC_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

extern int bg;
extern sf::RenderWindow window;
extern sf::Event event;
extern sf::Clock clk;
extern sf::Music music;
extern sf::Font arial;

enum PlatformType
{
    regular,
    spike,
    moving,
    movingspike,
    bouncing
};
enum ItemType
{
    nothing,
    coin,
    booster,
    invincibility,
    slowdown,
    gem
};

#define XButton event.mouseButton.x * 1280 / window.getSize().x
#define YButton event.mouseButton.y * 720 / window.getSize().y
#define XCursor event.mouseMove.x * 1280 / window.getSize().x
#define YCursor event.mouseMove.y * 720 / window.getSize().y

void icon();
void intro();
int menu();
void drawbg();

#endif