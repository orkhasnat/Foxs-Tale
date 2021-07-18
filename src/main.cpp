//#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.hpp"
#include "misc.hpp"

int main()
{
    srand(time(0));
    arial.loadFromFile("data/font/arial.ttf");

    int choice;

    window.create(sf::VideoMode(1280, 720), "Rapid Roll Advanced");
    icon();
    intro();

    while (window.isOpen())
    {
        choice = menu();

        if (choice == 1)
        {
            Game game;
            game.run();
            //Save records
        }

        else if (choice == 2)
        {
            //high scores
        }

        else if (choice == 3)
        {
            //instructions
        }

        else if (choice == 4)
        {
            //credits

            std::cout << '\n';
            std::cout << "Gameplay Concept:\nRapid Roll\nNokia\n\n";
            std::cout << "Backgrounds:\nThe First Tree\nBy David Wehle\n\n";
            std::cout << "Music:\n\"Gravity Falls Main Title Theme\"\nBy Brad Breeck\nFrom Gravity Falls- Created By Alex Hirsh\nA Television Animation By Disney\n\n";
        }

        else
            window.close();
    }

    return 0;
}
