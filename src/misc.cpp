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
    sound.openFromFile("data/audio/intro.ogg"); // // Check this, Tariq: The same music for the menu and the intro feels weird. You should pick a different music. Currently I have switched it back to the Rapid Roll intro because your fox kinda looks like the Rapid Roll Mascot. Change it if you want but don't use the same music as the menu.
    sound.setLoop(0);
    sound.setVolume(10);
    sound.play();

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

            if(event.type==sf::Event::KeyPressed || (event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left))
            {
                window.clear();
                window.display();
                return;
            }
        }

        if(clk.getElapsedTime().asMilliseconds()>50)
        {
            rect.left+=720;
            if(rect.left>14400-720)
            {
                rect.left=0;
                rect.top+=720;
                if(rect.top>=2880) return;
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
    int i, choice, active=1;
    sf::Music sound;
    sound.openFromFile("data/audio/menu.ogg");
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

            if(event.type==sf::Event::TextEntered && event.text.unicode>'0' && event.text.unicode<'6')
            {
                choice=event.text.unicode-'0';
                return choice%5;
            }

            else if(event.type==sf::Event::KeyPressed) switch(event.key.code)
            {
            case sf::Keyboard::Up:
                text[active].setFillColor(inactive);
                active+=5;
                active--;
                active%=5;
                break;

            case sf::Keyboard::Down:
                text[active].setFillColor(inactive);
                active+=5;
                active++;
                active%=5;
                break;

            case sf::Keyboard::Enter:
            case sf::Keyboard::Right:
                return active;
            case sf::Keyboard::Space:
                bg++;
            }

            if(event.type==sf::Event::MouseMoved) // Check this, Tariq: Mouse Controls added to the menu
            {
                for(i=0; i<5; i++) if(text[i].getGlobalBounds().contains(XCursor, YCursor))
                {
                    text[active].setFillColor(inactive);
                    active=i;
                    break;
                }
            }

            if(event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)
            {
                for(i=0; i<5; i++) if(text[i].getGlobalBounds().contains(XButton, YButton))
                {
                    text[active].setFillColor(inactive);
                    active=i;
                    return active;
                }
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

void drawbg()
{
    if(!window.isOpen()) return;
    window.clear();

    sf::Texture texture;
    texture.loadFromFile("data/img/bg/"+std::to_string(bg&7)+".jpg");
    sf::Sprite sprite;
    sprite.setTexture(texture);

    window.draw(sprite);
}
