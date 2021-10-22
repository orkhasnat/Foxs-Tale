#include "misc.hpp"

int bg = 0;
sf::RenderWindow window;
sf::Event event;
sf::Clock clk;
sf::Music music;
sf::Font arial;
sf::Font ArchitectsDaughter;

void icon()
{
    sf::Image Icon;
    Icon.loadFromFile("data/img/RR.png");

    window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());
}

void intro()
{
    sf::Texture texture;
    texture.loadFromFile("data/img/intro/foxie.png");
    sf::IntRect rect(0, 0, 720, 720);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(240, 0);

    sf::Music sound;
    sound.openFromFile("data/audio/intro.ogg"); // The same music for the menu and the intro feels weird. A different music is recommended. Currently I have temporarily switched it back to the Rapid Roll intro.
    sound.setLoop(0);
    sound.setVolume(10);
    sound.play();

    clk.restart();

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
            else if(event.type==sf::Event::KeyPressed || (event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left))
            {
                window.clear();
                window.display();
                return;
            }
        }

        if (clk.getElapsedTime().asMilliseconds() > 50)
        {
            rect.left += 720;
            if (rect.left > 14400 - 720)
            {
                rect.left = 0;
                rect.top += 720;
                if (rect.top >= 2880)
                    return;
            }

            sprite.setTextureRect(rect);
            clk.restart();
        }

        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }
}

int menu()
{
    int i, choice, active = 1;
    sf::Music sound;
    sound.openFromFile("data/audio/menu.ogg");
    sound.setLoop(1);
    sound.setVolume(10);
    sound.play();

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(420, 720));
    rect.setFillColor(sf::Color(0, 0, 0, 200));
    rect.setPosition(0, 0);

    sf::Color inactive = sf::Color::White, selected = sf::Color::Red;
    sf::Text text[5];
    for (i = 0; i < 5; i++)
    {
        text[i].setFont(ArchitectsDaughter);
        text[i].setCharacterSize(30);
        text[i].setFillColor(inactive);
        text[i].setStyle(sf::Text::Bold);
        text[i].setPosition(120, 120 * i - 15);
    }
    text[0].setPosition(120, 600 - 15);

    text[1].setString("New Game");
    text[2].setString("High Scores");
    text[3].setString("Instructions");
    text[4].setString("Credits");
    text[0].setString("Exit");

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
            else if(event.type==sf::Event::TextEntered && event.text.unicode>'0' && event.text.unicode<'6')
            {
                choice = event.text.unicode - '0';
                return choice % 5;
            }

            else if(event.type==sf::Event::KeyPressed) 
              switch(event.key.code)
            {
            case sf::Keyboard::Up:
                text[active].setFillColor(inactive);
                active+=4;
                active%=5;
                break;

            case sf::Keyboard::Down:
                text[active].setFillColor(inactive);
                active++;
                active%=5;
                break;

            case sf::Keyboard::Enter:
            case sf::Keyboard::Right:
                return active;
            case sf::Keyboard::Space:
                bg++;
            }

            else if(event.type==sf::Event::MouseMoved)
            {
                for(i=0; i<5; i++) if(text[i].getGlobalBounds().contains(XCursor, YCursor))
                {
                case sf::Keyboard::Up:
                    text[active].setFillColor(inactive);
                    active += 5;
                    active--;
                    active %= 5;
                    break;
            else if(event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)
            {
                for(i=0; i<5; i++) if(text[i].getGlobalBounds().contains(XButton, YButton)) return i;
            }
        }

        window.clear();
        drawbg();
        window.draw(rect);
        text[active].setFillColor(selected);
        for (i = 0; i < 5; i++)
            window.draw(text[i]);
        window.display();
    }
    return -1;
}

std::string scanfromscreen(sf::Text& text, sf::IntRect rect)
{
    if(!window.isOpen()) return "";

    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);
    sf::Sprite screenshot;
    screenshot.setTexture(texture);
    screenshot.scale(1280.0/window.getSize().x, 720.0/window.getSize().y);

    std::string str="";
    text.setString(str);
    text.setPosition(rect.left, rect.top);

    bool flag=1;
    while(flag && window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed) window.close();

            else if(event.type==sf::Event::TextEntered && ((event.text.unicode>='a' && event.text.unicode<='z') || (event.text.unicode>='A' && event.text.unicode<='Z') || (event.text.unicode>='0' && event.text.unicode<='9') || event.text.unicode==' '))
            {
                std::string temp="0";
                temp[0]=event.text.unicode;

                text.setString(str+temp);
                if(text.getGlobalBounds().width > rect.width) {temp="\n"+temp; text.setString(str+temp);}
                if(text.getGlobalBounds().height > rect.height) temp="";

                str=str+temp;
                text.setString(str);
            }

            else if((event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left) || (event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Enter)) flag=0;

            else if(event.type==sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Backspace && str.length())
                {
                    str=str.substr(0, str.length()-1);
                    if(str.length()) if(str[str.length()-1]=='\n') str=str.substr(0, str.length()-1);
                }
                else if(event.key.code==sf::Keyboard::Escape) str="";

                text.setString(str);
            }
        }

        window.draw(screenshot);
        window.draw(text);
        window.display();
    }

    return str;
}
std::string scanfromscreen(sf::Text &text, sf::IntRect rect)
{
    if (!window.isOpen())
        return "";

    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);
    sf::Sprite screenshot;
    screenshot.setTexture(texture);

    std::string str = "";
    text.setString(str);
    text.setPosition(rect.left, rect.top);

    bool flag = 1;
    while (flag && window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::TextEntered && ((event.text.unicode >= 'a' && event.text.unicode <= 'z') || (event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= '0' && event.text.unicode <= '9') || event.text.unicode == ' '))
            {
                if (event.text.unicode == ' ')
                    continue;

                std::string temp = "0";
                temp[0] = event.text.unicode;

                text.setString(str + temp);
                if (text.getGlobalBounds().width > rect.width)
                {
                    temp = "\n" + temp;
                    text.setString(str + temp);
                }
                if (text.getGlobalBounds().height > rect.height)
                    temp = "";

                str = str + temp;
                text.setString(str);
            }

            else if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))
                flag = 0;

            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Backspace && str.length())
                {
                    str = str.substr(0, str.length() - 1);
                    if (str.length())
                        if (str[str.length() - 1] == '\n')
                            str = str.substr(0, str.length() - 1);
                }
                else if (event.key.code == sf::Keyboard::Escape)
                    str = "";

                text.setString(str);
            }
        }

        window.draw(screenshot);
        window.draw(text);
        window.display();
    }

    return str;
}
void drawbg()
{
    if (!window.isOpen())
        return;
    window.clear();

    sf::Texture texture;
    texture.loadFromFile("data/img/bg/" + std::to_string(bg & 7) + ".jpg");
    sf::Sprite sprite;
    sprite.setTexture(texture);

    window.draw(sprite);
}

void drawframe()
{
    sf::RectangleShape frame;

    frame.setSize(sf::Vector2f(400, 600));
    frame.setFillColor(sf::Color(255, 255, 255, 200));
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(5);
    frame.setPosition(800, 100);

    window.draw(frame);
}

void readrecords(std::set<std::pair<int, std::string>> &records, std::ifstream &fin)
{
    for(int i=0; i<10; i++)
    {
        if(!fin) return;

        int score;
        std::string name;
        char temp;

        fin >> score;
        fin >> temp;
        if(!fin) return;

        std::getline(fin, name, '#');
        records.insert({score, name});
    }
}

void displayrecords(const std::set<std::pair<int, std::string>> &records)
{
    int i;
    sf::Music sound;
    sound.openFromFile("data/audio/menu.ogg"); // A different music is recommended
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

void roll(std::vector<std::string>& text)
{
    int i=0;
    sf::Music sound;
    sound.openFromFile("data/audio/menu.ogg"); // A different music is recommended
    sound.setLoop(1);
    sound.setVolume(10);
    sound.play();
    sf::Text lines;

    lines.setFont(ArchitectsDaughter);
    lines.setCharacterSize(25);
    lines.setFillColor(sf::Color::White);
    lines.setOutlineThickness(2);
    lines.setOutlineColor(sf::Color::Black);
    lines.setStyle(sf::Text::Bold);
    lines.setPosition(810, 650);

    lines.setString("Something");
    int h=lines.getGlobalBounds().height;
    lines.setString(text[i]);

    clk.restart();

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
                return;
            }

            if(event.type==sf::Event::KeyPressed || (event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)) return;
        }

        if(clk.getElapsedTime().asMilliseconds()>500) // Check the time
        {
            i++;
            lines.move(0, -h);
            if(i<text.size()) lines.setString(lines.getString()+"\n"+text[i]);

            if(lines.getPosition().y<100)
            {
                lines.move(0, h);
                int j;

                std::string str=lines.getString();
                for(j=0; j<str.size(); j++) if(str[j]=='\n') break;
                if(j<str.size()) lines.setString(str.substr(j+1, str.size()));
                else lines.setString("");
            }

            clk.restart();
        }

        if(!lines.getString().getSize()) return;

        drawbg();
        drawframe();
        window.draw(lines);
        window.display();
    }
}

