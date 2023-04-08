#include "misc.hpp"

int bg=0;
sf::RenderWindow window;
sf::Event event;
sf::Clock clk;
sf::Music music;
sf::Font arial;
sf::Font ArchitectsDaughter;

void icon()
{
    sf::Image Icon;
    Icon.loadFromFile("../data/img/RR.png");

    window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());
}

void intro()
{
    sf::Texture texture;
    sf::Sprite sprite;
    int cover=rand()%18;

    sf::Music sound;
    sound.openFromFile("../data/audio/intro.ogg");
    sound.setLoop(0);
    sound.setVolume(10);
    sound.play();

    while(sound.getStatus()==sf::Music::Playing)
    {
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
                return;
            }

            if(event.type==sf::Event::KeyPressed || (event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left))
            {
                window.clear();
                window.display();
                return;
            }
        }

        texture.loadFromFile("../data/img/intro/"+std::to_string(cover)+".jpg");
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
        window.clear();
    }

    window.display();
}

int menu()
{
    int i, choice, active=1;
    sf::Music sound;
    sound.openFromFile("../data/audio/menu.ogg");
    sound.setLoop(1);
    sound.setVolume(10);
    sound.play();

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(420, 720));
    rect.setFillColor(sf::Color(0, 0, 0, 200));
    rect.setPosition(0, 0);

    sf::Color inactive=sf::Color::White, selected=sf::Color::Red;
    sf::Text text[5];
    for(i=0; i<5; i++)
    {
        text[i].setFont(ArchitectsDaughter);
        text[i].setCharacterSize(30);
        text[i].setFillColor(inactive);
        text[i].setStyle(sf::Text::Bold);
        text[i].setPosition(120, 120*i-15);
    }

    text[0].setPosition(120, 600-15);
    text[1].setString("New Game");
    text[2].setString("High Scores");
    text[3].setString("Instructions");
    text[4].setString("Credits");
    text[0].setString("Exit");

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
                return 0;
            }

            else if(event.type==sf::Event::TextEntered && event.text.unicode>'0' && event.text.unicode<'6')
            {
                choice=event.text.unicode-'0';
                return choice%5;
            }

            else if(event.type==sf::Event::KeyPressed) switch(event.key.code)
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
                    text[active].setFillColor(inactive);
                    active=i;
                    break;
                }
            }

            else if(event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)
            {
                for(i=0; i<5; i++) if(text[i].getGlobalBounds().contains(XButton, YButton)) return i;
            }
        }

        window.clear();
        drawbg();
        window.draw(rect);
        text[active].setFillColor(selected);
        for(i=0; i<5; i++) window.draw(text[i]);
        window.display();
    }
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

void drawbg()
{
    if(!window.isOpen()) return;
    window.clear();

    sf::Texture texture;
    texture.loadFromFile("../data/img/bg/"+std::to_string(bg&7)+".jpg");
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

std::vector<std::string> readlines(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

// void roll(std::vector<std::string> &text)
// {
//     int i = 0;
//     sf::Music sound;
//     sound.openFromFile("data/audio/menu.ogg"); // A different music is recommended
//     sound.setLoop(1);
//     sound.setVolume(10);
//     sound.play();
//     sf::Text lines;

//     lines.setFont(ArchitectsDaughter);
//     lines.setCharacterSize(25);
//     lines.setFillColor(sf::Color::White);
//     lines.setOutlineThickness(2);
//     lines.setOutlineColor(sf::Color::Black);
//     lines.setStyle(sf::Text::Bold);
//     lines.setPosition(810, 650);

//     lines.setString("Something");
//     int h = lines.getGlobalBounds().height;
//     lines.setString(text[i]);

//     clk.restart();

//     while (window.isOpen())
//     {
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//                 return;
//             }

//             if (event.type == sf::Event::KeyPressed || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))
//                 return;
//         }

//         if (clk.getElapsedTime().asMilliseconds() > 500) // Check the time
//         {
//             i++;
//             lines.move(0, -h);
//             if (i < text.size())
//                 lines.setString(lines.getString() + "\n" + text[i]);

//             if (lines.getPosition().y < 100)
//             {
//                 lines.move(0, h);
//                 int j;

//                 std::string str = lines.getString();
//                 for (j = 0; j < str.size(); j++)
//                     if (str[j] == '\n')
//                         break;
//                 if (j < str.size())
//                     lines.setString(str.substr(j + 1, str.size()));
//                 else
//                     lines.setString("");
//             }

//             clk.restart();
//         }

//         if (!lines.getString().getSize())
//             return;

//         drawbg();
//         drawframe();
//         window.draw(lines);
//         window.display();
//     }
// }