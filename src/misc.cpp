#include "misc.hpp"

int bg = 0;
sf::RenderWindow window;
sf::Event event;
sf::Clock clk;
sf::Music music;
sf::Font arial;

void icon()
{
    sf::Image logo;
    logo.loadFromFile("data/img/icon.png");

    window.setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());
}

void intro(void)
{
    sf::Texture texture;
    sf::Sprite sprite;
    int cover = rand() % 18;

    sf::Music sound;
    sound.openFromFile("data/audio/intro.ogg");
    sound.setLoop(0);
    sound.setVolume(10);
    sound.play();

    while (sound.getStatus() == sf::Music::Playing)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyPressed || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))
            {
                sound.stop();
                window.clear();
                window.display();
                return;
            }
        }

        texture.loadFromFile("data/img/intro/" + std::to_string(cover) + ".jpg");
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
        window.clear();
    }

    window.display();
}

int menu()
{
    sf::Text text;
    text.setFont(arial);
    text.setString("Go to console");

    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(50, 50);

    window.clear();
    window.draw(text);
    window.display();

    int choice;
    puts("1. New Game");
    puts("2. High Scores");
    puts("3. Instructions");
    puts("4. Credits");
    puts("5. Exit");
    printf("Enter Choice: ");
    std::cin >> choice;

    return choice % 5;
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