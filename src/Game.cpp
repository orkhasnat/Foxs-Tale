#include "Game.hpp"

void Game::newball()
{
    Queue<Platform*> availablePlatforms;
    for(int i=0; i<platforms.size(); i++) if(typeid(*platforms[i])==typeid(Platform)) availablePlatforms.enqueue(platforms[i]);

    if(availablePlatforms.isEmpty())
    {
        levitate(1);
        newball();
    }

    else if(availablePlatforms.size()<2)
    {
        ball=new Ball(availablePlatforms[0]);
        return;
    }

    ball=new Ball(availablePlatforms[2+rand()%(availablePlatforms.size()-2)]);
}

void Game::newPlatform(PlatformType platformtype = regular)
{
    int temp=rand()%401;
    if(temp<100 && !(rand()&7)) temp=0;

    ItemType itemtype=nothing;
    switch(rand()%100)
    {
    case 0 ... 10:
        if(!score) break;
        itemtype=coin;
        break;

    case 11 ... 15:
        if(!score) break;
        itemtype=booster;
        break;

    case 16 ... 20:
        if(!score) break;
        itemtype=protection;
        break;

    case 21 ... 25:
        if(!score) break;
        if(runspeed<3) break;
        itemtype=slowdown;
        break;

    case 97:
        if(!score) break;
        if(score>4000) if(rand()&3) break;
        itemtype=gem;
        break;
    }

    switch(platformtype)
    {
    case regular:
        platforms.enqueue(new Platform(800+temp, itemtype));
        break;

    case spike:
        platforms.enqueue(new Spike(800+temp));
        break;

    case moving:
        platforms.enqueue(new MovingPlatform(800+temp, itemtype));
        break;

    case movingspike:
        //platforms.enqueue(new MovingSpike(800+temp));
        break;

    case bouncing:
        platforms.enqueue(new BouncyPlatform(800+temp));
        break;
    }
}

void Game::addPlatform()
{
    if(platforms.back()->sprite.getPosition().y<700-200) newPlatform();
    else if(platforms.back()->sprite.getPosition().y<700-100) if(rand()%5<3) newPlatform();

    if(platforms.back()->sprite.getPosition().y>=700-100) return;
    if(platforms.size()<4) return;
    if(score<500) return;

    for(int i=0; i<4; i++)
    {
        Platform* temp=platforms[platforms.size()-1-i];
        if(temp->getPlatformType()!=regular) return;
    }
    if(score>1000) if(!(rand()%10)) newPlatform(moving);

    for(int i=0; i<4; i++)
    {
        Platform* temp=platforms[platforms.size()-1-i];
        if(temp->getPlatformType()!=regular) return;
    }
    if(score>1000) if(!(rand()%10)) newPlatform(bouncing);

    for(int i=0; i<4; i++)
    {
        Platform* temp=platforms[platforms.size()-1-i];
        if(temp->getPlatformType()!=regular) return;
    }
    if(rand()%5<3) newPlatform(spike);
}

void Game::manageevents()
{
    int button=2;
    clk.restart();
    int framerate=15+3*(runspeed-1-(2*!!slowdowntime));

    while(window.pollEvent(event) || clk.getElapsedTime().asSeconds()<1.0/framerate)
    {
        if(event.type==sf::Event::Closed)
        {
            window.close();
            return;
        }

        else if(event.type==sf::Event::KeyPressed) switch(event.key.code)
        {
        case sf::Keyboard::Left:
            if(button)
            {
                leftarrow();
                if(!window.isOpen()) return;
                button--;
            }
            break;

        case sf::Keyboard::Right:
            if(button)
            {
                rightarrow();
                if(!window.isOpen()) return;
                button--;
            }
            break;

        case sf::Keyboard::Space:
            pause();
            if(!window.isOpen()) return;
        }
    }
}

void Game::pause()
{
    playing.pause();
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
                return;
            }

            else if(event.type==sf::Event::Resized)
            {
                draw();
                window.display();
            }

            else if(event.type==sf::Event::KeyPressed || (event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left))
            {
                playing.play();
                return;
            }
        }
    }
}

void Game::levelcheck(int temp)
{
    if(score/1000>temp/1000)
    {
        bg++;
        if(runspeed<6) runspeed++;
    }
}

void Game::drawscore() const
{
    sf::Text text;
    text.setFont(arial);
    text.setString("Score: "+std::to_string(score));

    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(800, 55);

    window.draw(text);
}

void Game::drawremaining() const
{
    sf::CircleShape circle[life];
    for(int i=0; i<life; i++)
    {
        circle[i].setRadius(12);
        circle[i].setOutlineThickness(2);
        circle[i].setFillColor(sf::Color::Red);
        circle[i].setOutlineColor(sf::Color::Black);
        circle[i].setPosition(1200-30*(i+1), 65);
        window.draw(circle[i]);
    }
}

void Game::draw()
{
    drawbg();
    drawremaining();
    drawscore();
    drawframe();
    window.draw(spikes);
    for(int i=0; i<platforms.size(); i++)
    {
        window.draw(platforms[i]->sprite);
        if(platforms[i]->getItem()) window.draw(platforms[i]->getItem()->sprite);
    }
    if(ball) window.draw(ball->circle);
}

void Game::levitate(const int movement)
{
    if(!movement) return;

    for(int i=0; i<platforms.size(); i++)
    {
        platforms[i]->move();

        if(platforms[i]->sprite.getPosition().y<=110)
        {
            if(ball) if(ball->standingOn==platforms[i]) burst();
            if(!window.isOpen()) return;
            if(!life) return;
            delete platforms.front();
            platforms.dequeue();
            --i;
        }
    }

    addPlatform();
    levitate(movement-1);
}

void Game::leftarrow()
{
    int ballspeed=8*(1+0.5*!!(ball->isBoosted));

    while(ballspeed--)
    {
        ball->circle.move(-1, 0);
        if(ball->circle.getPosition().x-ball->circle.getRadius()-ball->circle.getOutlineThickness()<800) ball->circle.move(+1, 0);

        if((ball->findPlatform(platforms))==2) getBonus();
        if((ball->findPlatform(platforms))==3) burst();
    }
}

void Game::rightarrow()
{
    int ballspeed=8*(1+0.5*!!(ball->isBoosted));

    while(ballspeed--)
    {
        ball->circle.move(1, 0);
        if(ball->circle.getPosition().x+ball->circle.getRadius()+ball->circle.getOutlineThickness()>1200) ball->circle.move(-1, 0);

        if((ball->findPlatform(platforms))==2) getBonus();
        if((ball->findPlatform(platforms))==3) burst();
    }
}

void Game::fall()
{
    int temp=score, land;
    score+=1+rand()%10;
    levelcheck(temp);

    if(land=ball->findPlatform(platforms))
    {
        if(land==2) getBonus();
        else if(land==3) burst();
        else if(land==4) bounce();
        return;
    }

    ball->circle.move(0, 10);
    if(land=ball->findPlatform(platforms))
    {
        if(land==2) getBonus();
        else if(land==3) burst();
        else if(land==4) bounce();
        return;
    }

    if(ball)
    {
        ball->circle.move(0, 10);
        if(ball->findPlatform(platforms)==2) getBonus();
        else if(ball->findPlatform(platforms)==3) burst();
        else if(ball->findPlatform(platforms)==4) bounce();
        else if(ball->circle.getPosition().y>=700) burst();
    }
}

void Game::bounce()
{
    score+=1+rand()%20;

    for(int i=5-rand()%5; i; i--)
    {
        ball->circle.move(0, -20);
        if(ball->findPlatform(platforms))
        {
            ball->circle.move(0, 40);
            ball->standingOn=nullptr;
            return;
        }

        if(ball->circle.getPosition().y-2*ball->circle.getRadius()-ball->circle.getOutlineThickness()<=110)
        {
            burst();
            return;
        }
    }
}

void Game::getBonus()
{
    int temp;

    switch(ball->standingOn->getItemType())
    {
    case coin:
        temp=score;
        ball->standingOn->getItem()->bonus(&score);
        if(score/1000>temp/1000)
        {
            bg++;
            if(runspeed<6) runspeed++;
        }
        break;

    case booster:
        ball->standingOn->getItem()->bonus(&ball->isBoosted);
        ball->circle.setFillColor(sf::Color::Yellow);
        ball->circle.setOutlineColor(sf::Color::Red);
        ball->isBoosted+=ball->isProtected;
        ball->isProtected=0;
        break;

    case protection:
        ball->standingOn->getItem()->bonus(&ball->isProtected);
        ball->circle.setFillColor(sf::Color::White);
        ball->circle.setOutlineColor(sf::Color::Blue);
        ball->isProtected+=ball->isBoosted;
        ball->isBoosted=0;
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
    sf::Music burstingball;
    burstingball.openFromFile("data/audio/burst.ogg");
    burstingball.setLoop(0);
    burstingball.setVolume(10);

    delete ball;
    ball=nullptr;
    life--;
    slowdowntime=0;

    if(life) newball();
    if(ball) if(ball->findPlatform(platforms)==2) getBonus();
    draw();
    window.display();

    burstingball.play();
    while(burstingball.getStatus()==sf::Music::Playing);
    pause();
}

// public functions

Game::Game(): score(0), life(3), runspeed(1), slowdowntime(0)
{
    newPlatform();
    levitate(15+rand()%5);
    newball();

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
    while(!platforms.isEmpty())
    {
        delete platforms.front();
        platforms.dequeue();
    }
    if(ball) delete ball;
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

    while(window.isOpen() && life)
    {
        draw();
        window.display();

        manageevents();
        if(!window.isOpen()) continue;
        levitate(1);
        if(slowdowntime) slowdowntime--;

        if(ball)
        {
            if(ball->isFalling()) fall();
            if(ball) if(ball->standingOn) ball->circle.setPosition(ball->standingOn->sprite.getPosition().x+ball->standingOn->getballx(), ball->standingOn->sprite.getPosition().y);

            if(!window.isOpen()) continue;

            if(ball) if(ball->isBoosted)
            {
                ball->isBoosted--;

                if(!ball->isBoosted)
                {
                    ball->circle.setFillColor(sf::Color::Red);
                    ball->circle.setOutlineColor(sf::Color::Black);
                }
            }
            if(ball) if(ball->isProtected)
            {
                ball->isProtected--;

                if(!ball->isProtected)
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
