#include "Game.hpp"

void Game::newball()
{
    std::deque<Platform *> availablePlatforms;
    for (int i = 0; i < platforms.size(); i++)
        if (platforms[i]->getPlatformType() == regular)
            availablePlatforms.push_back(platforms[i]);

    if (availablePlatforms.size() < 2)
        ball = new Ball(availablePlatforms[0]);
    ball = new Ball(availablePlatforms[2 + rand() % (availablePlatforms.size() - 2)]);
}

void Game::newPlatform(PlatformType platformtype = regular)
{
    int temp = rand() % 401;
    if (temp < 100 && !(rand() & 7))
        temp = 0;

    ItemType itemtype = nothing;

    {
        int tempRandom = rand() % 100;
        if ((tempRandom >= 0) && (tempRandom < 11))
        {
            if (score)
                itemtype = coin;
        }
        else if ((tempRandom >= 11) && (tempRandom < 16))
        {
            if (score)
                itemtype = booster;
        }
        else if ((tempRandom >= 16) && (tempRandom < 21))
        {
            if (score)
                itemtype = invincibility;
        }
        else if ((tempRandom >= 21) && (tempRandom < 26))
        {
            if (score && runspeed > 2)
                itemtype = slowdown;
        }
        else if (tempRandom == 97)
        {
            if (score)
            {
                if (score > 4000)
                    if (!(rand() & 3))
                        itemtype = gem;
            }
        }
    }

    switch (platformtype)
    {
    case regular:
        platforms.push_back(new Platform(800 + temp, itemtype));
        break;

    case spike:
        platforms.push_back(new Spike(800 + temp));
        break;

    case moving:
        //platforms.push_back(new MovingPlatform(800+temp, itemtype));
        break;

    case movingspike:
        //platforms.push_back(new MovingSpike(800+temp));
        break;

    case bouncing:
        //platforms.push_back(new BouncyPlatform(800+temp, itemtype));
        break;
    }
}

void Game::addPlatform()
{
    if (platforms.back()->sprite.getPosition().y < 700 - 120)
        newPlatform();
    else if (platforms.back()->sprite.getPosition().y < 700 - 90)
        if (rand() % 10 < 9)
            newPlatform();
        else if (platforms.back()->sprite.getPosition().y < 700 - 60)
            if (rand() & 3)
                newPlatform();
            else if (platforms.back()->sprite.getPosition().y < 700 - 30)
                if (rand() % 5 < 3)
                    newPlatform();

    if (platforms.back()->sprite.getPosition().y >= 700 - 60)
        return;
    if (platforms.size() < 4)
        return;
    if (score < 500) // until score reaches 500, all are regular
        return;

    for (int i = 0; i < 4; i++)
    {
        Platform *temp = platforms[platforms.size() - 1 - i];
        if (temp->getPlatformType() != regular)
            return;
    }
    if (score > 1000)
    { // no moving platform until score is 1000
        if (!(rand() % 10))
            newPlatform(moving);
    }

    for (int i = 0; i < 4; i++)
    {
        Platform *temp = platforms[platforms.size() - 1 - i];
        if (temp->getPlatformType() != regular)
            return;
    }

    if ((rand() % 5) < 3)
        newPlatform(spike);
}

void Game::manageevents()
{
    int button = 2;
    clk.restart();
    //int framerate=runspeed<=5? 8+3*(runspeed-1-(2*!!slowdowntime)): 25;
    int framerate = 10 + 4 * (runspeed - 1 - (2 * !!slowdowntime));

    while (window.pollEvent(event) || clk.getElapsedTime().asSeconds() < 1.0 / framerate)
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }

        else if (event.type == sf::Event::Resized)
        {
            draw();
            window.display();
        }

        else if (event.type == sf::Event::KeyPressed)
            switch (event.key.code)
            {
            case sf::Keyboard::Left:
                if (button)
                {
                    leftarrow();
                    if (!window.isOpen())
                        return;
                    button--;
                }
                break;

            case sf::Keyboard::Right:
                if (button)
                {
                    rightarrow();
                    if (!window.isOpen())
                        return;
                    button--;
                }
                break;

            case sf::Keyboard::Space:
                pause();
                if (!window.isOpen())
                    return;
            }
    }
}

void Game::pause()
{
    playing.pause();
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }

            if (event.type == sf::Event::Resized)
            {
                draw();
                window.display();
            }

            if (event.type == sf::Event::KeyPressed || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))
            {
                playing.play();
                return;
            }
        }
    }

    playing.play();
}

void Game::draw() const
{
    drawbg();
    drawremaining();
    drawscore();
    window.draw(frame);
    window.draw(spikes);
    for (int i = 0; i < platforms.size(); i++)
    {
        window.draw(platforms[i]->sprite);
        if (platforms[i]->getItem())
            window.draw(platforms[i]->getItem()->sprite);
    }
    if (ball)
        window.draw(ball->circle);
}

void Game::levitate(const int movement)
{
    if (!movement)
        return;

    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i]->move();

        if (platforms[i]->sprite.getPosition().y <= 110)
        {
            if (ball)
                if (ball->standingOn == platforms[i])
                    burst();
            if (!window.isOpen())
                return;
            if (!life)
                return;
            delete platforms.front();
            platforms.pop_front();
            --i;
        }
    }

    addPlatform();
    levitate(movement - 1);
}

void Game::leftarrow()
{
    int ballspeed = 8 + 2 * (runspeed - (2 * !!slowdowntime));
    ballspeed *= 1 + 0.5 * !!(ball->isBoosted);

    while (ballspeed--)
    {
        ball->circle.move(-1, 0);
        if (ball->circle.getPosition().x - ball->circle.getRadius() - ball->circle.getOutlineThickness() < 800)
            ball->circle.move(+1, 0);

        if ((ball->findPlatform(platforms)) == 2)
            getBonus();
        if ((ball->findPlatform(platforms)) == 3)
            burst();
    }
}

void Game::rightarrow()
{
    int ballspeed = 8 + 2 * (runspeed - (2 * !!slowdowntime));
    ballspeed *= 1 + 0.5 * !!(ball->isBoosted);

    while (ballspeed--)
    {
        ball->circle.move(1, 0);
        if (ball->circle.getPosition().x + ball->circle.getRadius() + ball->circle.getOutlineThickness() > 1200)
            ball->circle.move(-1, 0);

        if ((ball->findPlatform(platforms)) == 2)
            getBonus();
        if ((ball->findPlatform(platforms)) == 3)
            burst();
    }
}

void Game::fall()
{
    int temp = score, temp2;
    score += 1 + rand() % 10;
    levelcheck(temp);

    if (temp2 = ball->findPlatform(platforms))
    {
        if (temp2 == 2)
            getBonus();
        if (temp2 == 3)
            burst();
        return;
    }

    temp = 20;
    while (temp > 10)
    {
        ball->circle.move(0, 10);
        if (temp2 = ball->findPlatform(platforms))
        {
            if (temp2 == 2)
                getBonus();
            if (temp2 == 3)
                burst();
            temp = 10;
        }
        temp -= 10;
    }
    if (ball)
    {
        ball->circle.move(0, temp);
        if (ball->findPlatform(platforms) == 2)
            getBonus();
        else if (ball->findPlatform(platforms) == 3)
            burst();
        else if (ball->circle.getPosition().y >= 700)
            burst();
    }
}

void Game::bounce()
{
    score += 1 + rand() % 20;
    ball->circle.move(0, -20);
    ball->isBouncing--;
    if (ball->circle.getPosition().y - 2 * ball->circle.getRadius() - ball->circle.getOutlineThickness() <= 110)
        burst();

    //Check for collision with platform
}

void Game::getBonus()
{
    int temp;

    switch (ball->standingOn->getItemType())
    {
    case coin:
        temp = score;
        ball->standingOn->getItem()->bonus(&score);
        if (score / 1000 > temp / 1000)
        {
            bg++;
            if (runspeed < 6)
                runspeed++;
        }
        break;

    case booster:
        ball->standingOn->getItem()->bonus(&ball->isBoosted);
        ball->circle.setFillColor(sf::Color::Yellow);
        ball->circle.setOutlineColor(sf::Color::Red);
        ball->isBoosted += ball->isProtected;
        ball->isProtected = 0;
        break;

    case invincibility:
        ball->standingOn->getItem()->bonus(&ball->isProtected);
        ball->circle.setFillColor(sf::Color::White);
        ball->circle.setOutlineColor(sf::Color::Blue);
        ball->isProtected += ball->isBoosted;
        ball->isBoosted = 0;
        break;

    case slowdown:
        ball->standingOn->getItem()->bonus(&slowdowntime);
        break;

    case gem:
        ball->standingOn->getItem()->bonus(&life);
        break;
    }

    ball->standingOn->pickup();
}

void Game::burst()
{
    sf::Music burstingBall;
    burstingBall.openFromFile("data/audio/burst.ogg");
    burstingBall.setLoop(0);
    burstingBall.setVolume(10);

    delete ball;
    ball = nullptr;
    life--;
    slowdowntime = 0;

    if (life)
        newball();
    if (ball)
        if (ball->findPlatform(platforms) == 2)
            getBonus();
    draw();
    window.display();

    burstingBall.play();
    while (burstingBall.getStatus() == sf::Music::Playing)
        ;
    pause();
}

// public funcs

Game::Game() : score(0), life(3), runspeed(1), slowdowntime(0)
{
    newPlatform();
    levitate(10 + rand() % 5);
    newball();

    frame.setSize(sf::Vector2f(400, 600));
    frame.setFillColor(sf::Color(255, 255, 255, 200));
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(5);
    frame.setPosition(800, 100);

    texture.loadFromFile("data/img/Spikes_Flip.png");
    spikes.setTexture(texture);
    spikes.setTextureRect(sf::IntRect(0, 0, 400, 10));
    spikes.setPosition(800, 100);

    playing.openFromFile("data/audio/playing.ogg");
    playing.setVolume(10);
    playing.setLoop(true);
}

Game::~Game()
{
    for (int i = 0; i < platforms.size(); i++)
        delete platforms[i];
    if (ball)
        delete ball;
}

int Game::getScore() const
{
    return score;
}

void Game::run()
{
    playing.play();
    draw();
    window.display();
    pause();

    while (window.isOpen() && life)
    {
        draw();
        window.display();

        manageevents();
        if (!window.isOpen())
            continue;
        levitate(1);
        if (slowdowntime)
            slowdowntime--;

        if (ball)
        {
            if (ball->isFalling())
                fall();
            else if (ball->isBouncing)
                bounce();
            else
                ball->circle.setPosition(ball->standingOn->sprite.getPosition().x + ball->standingOn->getballx(), ball->standingOn->sprite.getPosition().y);

            if (!window.isOpen())
                continue;

            if (ball)
                if (ball->isBoosted)
                {
                    ball->isBoosted--;

                    if (!ball->isBoosted)
                    {
                        ball->circle.setFillColor(sf::Color::Red);
                        ball->circle.setOutlineColor(sf::Color::Black);
                    }
                }
            if (ball)
                if (ball->isProtected)
                {
                    ball->isProtected--;

                    if (!ball->isProtected)
                    {
                        ball->circle.setFillColor(sf::Color::Red);
                        ball->circle.setOutlineColor(sf::Color::Black);
                    }
                }
        }
    }

    playing.stop();
    bg++;
}