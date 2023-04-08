#include <bits/stdc++.h>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Game.hpp"
#include "misc.hpp"

int main()
{
    srand(time(0));
    arial.loadFromFile("../data/font/arial.ttf");
    ArchitectsDaughter.loadFromFile("../data/font/ArchitectsDaughter-Regular.ttf");

    window.create(sf::VideoMode(1280, 720), "Rapid Roll Advanced");
    icon();
    intro();

    int choice;

    std::set<std::pair<int, std::string>> records;
    std::ifstream fin("../data/High_Score.txt");
    readrecords(records, fin);
    fin.close();

    while(window.isOpen())
    {
        choice=menu();

        if(choice==1)
        {
            Game game;
            game.run();

            int score=game.getScore();
            if(newrecord(records, score)) addrecord(records, score);
        }

        else if(choice==2) displayrecords(records); //high scores

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

    std::ofstream fout("../data/High_Score.txt");
    for(auto it=records.begin(); it!=records.end(); it++) fout << it->first<< '#' << it->second << '#';

    return 0;
}
