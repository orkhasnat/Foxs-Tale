#include <bits/stdc++.h>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Game.hpp"
#include "misc.hpp"
#include "record.hpp"

void initialize()
{
    srand(time(0));
    arial.loadFromFile("../data/font/arial.ttf");
    ArchitectsDaughter.loadFromFile("../data/font/ArchitectsDaughter-Regular.ttf");
    readrecords();

    window.create(sf::VideoMode(1280, 720), "Rapid Roll Advanced");
    icon();
    intro();
}

int main()
{
    initialize();
    int choice;

    while(window.isOpen())
    {
        choice=menu();

        if(choice==1)
        {
            Game game;
            game.run();

            int score=game.getScore();
            if(isnewrecord(score)) addrecord(score);
        }

        else if(choice==2) displayrecords();

        else if(choice==3)
        {
            std::vector<std::string> instructions = readlines("../data/Instructions.txt");
            // roll(instructions);
            for(auto it: instructions) std::cout << it << '\n';
        }

        else if(choice==4)
        {
            std::vector<std::string> credits = readlines("../data/Credits.txt");
            // roll(credits);
            for(auto it: credits) std::cout << it << '\n';
        }

        else window.close();
    }

    saverecords();

    return 0;
}
