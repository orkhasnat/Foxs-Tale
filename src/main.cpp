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

    /*std::set<pair<int,string>> records;
    open file High_Score.txt in read mode
    readrecords(records, filepointer) // Read from High_Score.txt into records (set)
    close file pointer*/

    while(window.isOpen())
    {
        choice=menu();

        if(choice==1)
        {
            Game game;
            game.run();

            std::cout << "Your Score: " << game.getScore() << '\n';

            /*IF highscore.size()<10
                highscore.insert(game.getScore(), getPlayerName())
            ELSE IF game.getScore()>*(highscore.begin()).first
                highscore.erase(highscore.begin())
                highscore.insert(game.getScore(), getPlayerName())
            Don't need to do anything with the file*/
        }

        else if(choice==2)
        {
            //high scores

            //Display High Scores in the window from records (set) in reversed order
        }

        else if(choice==3)
        {
            //instructions
        }

        else if(choice==4)
        {
            //credits

            std::cout << '\n';
            std::cout << "Gameplay Concept:\nRapid Roll\nNokia\n\n";
            std::cout << "Backgrounds and Menu Music:\nThe First Tree\nBy David Wehle\n\n";
            std::cout << "Music:\n\"Gravity Falls Main Title Theme\"\nBy Brad Breeck\nFrom Gravity Falls- Created By Alex Hirsh\nA Television Animation By Disney\n\n";
            std::cout << "Intro Fox:\nTenor\nhttps://i2.wp.com/media1.tenor.com/images/ab80e83e9f913b87bb33cedf9cac2ef2/tenor.gif\n\n";
        }

        else window.close();
    }

    /*open file High_Score.txt in write mode
    writerecords(records, filepointer) // Clear High_Score.txt and then Write into High_Score.txt from records (set)
    close file pointer*/

    return 0;
}
