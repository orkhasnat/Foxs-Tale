#include <bits/stdc++.h>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Game.hpp"
#include "misc.hpp"

int main()
{
    srand(time(0));
    arial.loadFromFile("data/font/arial.ttf");
    ArchitectsDaughter.loadFromFile("data/font/ArchitectsDaughter-Regular.ttf");

    window.create(sf::VideoMode(1280, 720), "Rapid Roll Advanced");
    icon();
    intro();

    int choice;

    std::set<std::pair<int, std::string>> records;
    std::ifstream fin("data/High_Score.txt");
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

            if(records.size()<10)
            {
                drawrecord(score);

                sf::Music music;
                music.openFromFile("data/audio/playing.ogg"); // A different music is recommended
                music.setLoop(1);
                music.setVolume(10);
                music.play();

                sf::Text text;
                text.setFont(arial);
                text.setCharacterSize(30);
                text.setFillColor(sf::Color::White);
                text.setOutlineThickness(2);
                text.setOutlineColor(sf::Color::Black);
                text.setStyle(sf::Text::Bold);

                records.insert({game.getScore(), scanfromscreen(text, sf::IntRect(810, 110, 200, 40))});
                music.stop();
            }

            else if(score > records.begin()->first)
            {
                drawrecord(score);

                sf::Music music;
                music.openFromFile("data/audio/playing.ogg"); // A different music is recommended
                music.setLoop(1);
                music.setVolume(10);
                music.play();

                sf::Text text;
                text.setFont(arial);
                text.setCharacterSize(30);
                text.setFillColor(sf::Color::White);
                text.setOutlineThickness(2);
                text.setOutlineColor(sf::Color::Black);
                text.setStyle(sf::Text::Bold);

                records.erase(records.begin());
                records.insert({game.getScore(), scanfromscreen(text, sf::IntRect(810, 110, 200, 40))});
                music.stop();
            }
        }

        else if(choice==2) displayrecords(records); //high scores

        else if(choice==3)
        {
            //instructions
        }

        else if(choice==4)
        {
            //credits

            std::cout << '\n';
            std::cout << "Gameplay Concept:\nRapid Roll\nNokia\n\n";
            std::cout << "Backgrounds:\nThe First Tree\nBy David Wehle\n\n";
            std::cout << "Music:\n\"Gravity Falls Main Title Theme\"\nBy Brad Breeck\nFrom Gravity Falls- Created By Alex Hirsh\nA Television Animation By Disney\n\n\"Call of Destiny\"\nBy Josh Kramer\n\n";
            std::cout << "Intro Fox:\nTenor\nhttps://i2.wp.com/media1.tenor.com/images/ab80e83e9f913b87bb33cedf9cac2ef2/tenor.gif\n\n";
        }

        else window.close();
    }

    std::ofstream fout("data/High_Score.txt");
    for(auto it=records.begin(); it!=records.end(); it++) fout << it->first<< ' ' << it->second << '\n';

    return 0;
}
