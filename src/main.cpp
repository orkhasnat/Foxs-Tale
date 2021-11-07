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
    std::ifstream fin("data/hscore.savefile");

    readrecords(records, fin);
    fin.close();

    while (window.isOpen())
    {
        choice = menu();

        if (choice == 1)
        {
            Game game;
            game.run();

            int score = game.getScore();

            if (records.size() < 10)
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

            else if (score > records.begin()->first)
            {
                drawrecord(score);

                sf::Music music;
                music.openFromFile("data/audio/playing.ogg"); // A different music is recommended, but same as the one used a few lines above
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

        else if (choice == 2)
            displayrecords(records); //high scores
        else if (choice == 3)
        {
            //instructions
            std::vector<std::string> ins;
            ins.reserve(5);
            ins.push_back("Press <- to go Left");
            ins.push_back("Press -> to go Right");
            ins.push_back("Press Space to Pause");
            ins.push_back("Powerups:");
            ins.push_back("Eat the Yellow Coins");
            ins.push_back("for Bonus");
            ins.push_back("Eat the Cyan Gem for");
            ins.push_back("a larger Bonus");
            ins.push_back("Eat the Magenta Boost");
            ins.push_back("for a Speed Boost");
            ins.push_back("Eat the Green Blobs");
            ins.push_back("for Protection against spikes");
            ins.push_back("Eat the Blue balls");
            ins.push_back("to Slowdown time");
            roll(ins);
        }

        else if (choice == 4)
        {
            //credits
            // std::cout << '\n';
            // std::cout << "Gameplay Concept:\nRapid Roll\nNokia\n\n";
            // std::cout << "Backgrounds:\nThe First Tree\nBy David Wehle\n\n";
            // std::cout << "Music:\n\"Gravity Falls Main Title Theme\"\nBy Brad Breeck\nFrom Gravity Falls- Created By Alex Hirsh\nA Television Animation By Disney\n\n\"Call of Destiny\"\nBy Josh Kramer\n\n";
            // std::cout << "Intro Fox:\nTenor\nhttps://i2.wp.com/media1.tenor.com/images/ab80e83e9f913b87bb33cedf9cac2ef2/tenor.gif\n\n";

            std::vector<std::string> credits;
            credits.reserve(20);
            credits.push_back("Gameplay Concept:");
            credits.push_back("Rapid Roll");
            credits.push_back("Nokia");
            credits.push_back("");
            credits.push_back("Backgrounds:");
            credits.push_back("The First Tree");
            credits.push_back("By David Wehle");
            credits.push_back("");
            credits.push_back("Music:");
            credits.push_back("'Gravity Falls Main Title Theme'");
            credits.push_back("By Brad Breeck");
            credits.push_back("From Gravity Falls");
            credits.push_back("Created By Alex Hirsh");
            credits.push_back("A TV Animation By Disney");
            credits.push_back("");
            credits.push_back("'Call of Destiny'");
            credits.push_back("By Josh Kramer");
            roll(credits);
        }
        else
            window.close();
    }

    std::ofstream fout("data/hscore.savefile");
    for (auto it = records.begin(); it != records.end(); it++)
        fout << it->first << '#' << it->second << '#';
    return 0;
}
