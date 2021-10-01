#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Game.hpp"
#include "misc.hpp"

int main()
{
    srand(time(0));
    arial.loadFromFile("data/font/arial.ttf");
    ArchitectsDaughter.loadFromFile("data/font/ArchitectsDaughter-Regular.ttf");

    window.create(sf::VideoMode(1280, 720), "Fox's Tale");
    icon();
    intro();

    int choice;

    std::set<std::pair<int, std::string>> records;
    std::ifstream fin("High_Score.txt");
    readrecords(records, fin);
    fin.close();

    while (window.isOpen())
    {
        choice = menu();

        if (choice == 1)
        {
            Game game;
            game.run();

            std::cout << "Your Score: " << game.getScore() << '\n';

            if (records.size() < 10)
                records.insert({game.getScore(), getPlayerName()});
            else if (game.getScore() > records.begin()->first)
            {
                records.erase(records.begin());
                records.insert({game.getScore(), getPlayerName()});
            }
        }

        else if (choice == 2)
        {
            //Display High Scores in the window from records (set) in reversed order
            displayrecords(records);
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
            std::cout << "Backgrounds and Menu Music:\nThe First Tree\nBy David Wehle\n\n";
            std::cout << "Music:\n\"Gravity Falls Main Title Theme\"\nBy Brad Breeck\nFrom Gravity Falls- Created By Alex Hirsh\nA Television Animation By Disney\n\n";
            std::cout << "Intro Fox:\nTenor\nhttps://i2.wp.com/media1.tenor.com/images/ab80e83e9f913b87bb33cedf9cac2ef2/tenor.gif\n\n";
        }

        else
            window.close();
    }

    std::ofstream fout("High_Score.txt");
    for (auto it = records.begin(); it != records.end(); it++)
        fout << it->first << ' ' << it->second << '\n';

    return 0;
}
