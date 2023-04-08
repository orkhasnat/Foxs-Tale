#include "record.hpp"

std::set<std::pair<int, std::string>> records;

void readrecords()
{
    std::ifstream fin("../data/High_Score.txt");

    for (int i = 0; i < 10; i++)
    {
        int score;
        std::string name;

        if (!(fin >> score)) break;
        std::getline(fin >> std::ws, name);

        records.insert({ score, name });
    }

    fin.close();
}


void saverecords()
{
    std::ofstream fout("../data/High_Score.txt");
    for(auto it=records.begin(); it!=records.end(); it++) fout << it->first << " " << it->second << std::endl;
}


void displayrecords()
{
    int i;
    sf::Music sound;
    sound.openFromFile("../data/audio/menu.ogg"); // A different music is recommended
    sound.setLoop(1);
    sound.setVolume(10);
    sound.play();

    sf::Text heading[2];
    sf::Text score[10][2];

    for(i=0; i<2; i++)
    {
        heading[i].setFont(arial);
        heading[i].setCharacterSize(30);
        heading[i].setFillColor(sf::Color::White);
        heading[i].setOutlineThickness(2);
        heading[i].setOutlineColor(sf::Color::Black);
        heading[i].setStyle(sf::Text::Bold);
        heading[i].setPosition(810+250*i, 55);
    }
    heading[0].setString("Name");
    heading[1].setString("Score");

    i=0;
    for(auto it=records.rbegin(); it!=records.rend(); it++, i++)
    {
        score[i][0].setFont(arial); score[i][1].setFont(arial);
        score[i][0].setCharacterSize(30); score[i][1].setCharacterSize(30);
        score[i][0].setFillColor(sf::Color::Yellow); score[i][1].setFillColor(sf::Color::Yellow);
        score[i][0].setOutlineThickness(2); score[i][1].setOutlineThickness(2);
        score[i][0].setOutlineColor(sf::Color::Black); score[i][1].setOutlineColor(sf::Color::Black);
        score[i][0].setStyle(sf::Text::Bold); score[i][1].setStyle(sf::Text::Bold);
        score[i][0].setPosition(810, 110+60*i); score[i][1].setPosition(1060, 110+60*i);

        score[i][0].setString(it->second); score[i][1].setString(std::to_string(it->first));
    }

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
                return;
            }

            else if(event.type==sf::Event::KeyPressed || (event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)) return;
        }

        drawbg();
        drawframe();
        window.draw(heading[0]);
        window.draw(heading[1]);
        for(i=0; i<records.size(); i++)
        {
            window.draw(score[i][0]);
            window.draw(score[i][1]);
        }
        window.display();
    }
}

void drawrecord(int score)
{
    drawbg();
    drawframe();

    sf::Text text;
    text.setFont(arial);
    text.setString("New High Score: "+std::to_string(score)+"\nEnter Your Name");

    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(800, 25);

    window.draw(text);
}

bool isnewrecord(int score)
{
    return records.size()<10 || score>records.begin()->first;
}

void addrecord(int score)
{
    drawrecord(score);

    sf::Music music;
    music.openFromFile("../data/audio/playing.ogg"); // A different music is recommended
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

    if(records.size()>=10) records.erase(records.begin());
    records.insert({score, scanfromscreen(text, sf::IntRect(810, 110, 200, 40))});
    music.stop();
}