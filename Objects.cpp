#include "Objects.hpp"
#include "App.hpp"
#include <iostream>
#include <math.h>

double dj::Sprite::getRealPosX()
{
    double resistanceX = this->resistanceX;
    if (this->speedX * this->resistanceX > 0)
        resistanceX *= -1;
    else if (this->speedX == 0)
        resistanceX = 0;
    double realPosition = this->baseX + this->clockX.getElapsedTime().asMilliseconds() *
                                            (this->speedX + resistanceX * this->clockX.getElapsedTime().asMilliseconds() / 2);
    if (abs(resistanceX * this->clockX.getElapsedTime().asMilliseconds()) >= abs(this->speedX) && this->speedX != 0)
    {
        this->speedX = 0;
        this->baseX = realPosition;
        this->clockX.restart();
    }
    return realPosition;
}

double dj::Sprite::getRealPosY()
{
    return this->baseY + this->clockY.getElapsedTime().asMilliseconds() *
                             (this->speedY + this->gravityAcceleration * this->clockY.getElapsedTime().asMilliseconds() / 2);
}

void dj::Sprite::checkForMinSpeedY()
{
}

int dj::Sprite::updateBasePosX()
{
    if (this->clockX.getElapsedTime().asMilliseconds() < dj::minBaseCoordinatesUpdateInterval)
        return -1;
    this->baseX = this->getRealPosX();
    return this->clockX.restart().asMilliseconds();
}
int dj::Sprite::updateBasePosY()
{
    if (this->clockY.getElapsedTime().asMilliseconds() < dj::minBaseCoordinatesUpdateInterval)
        return -1;
    this->baseY = this->getRealPosY();
    return this->clockY.restart().asMilliseconds();
}

void dj::MainBallSprite::tick(std::vector<sf::Event> events, App &app)
{
    this->setPosition(this->getRealPosX(), this->getRealPosY());
    double departure = this->getRealPosY() + this->getGlobalBounds().height - app.get_window().getSize().y;
    if (departure >= 0)
    {
        int seconds = this->updateBasePosY();
        this->setPosition(this->getRealPosX(), app.get_window().getSize().y - this->getGlobalBounds().height);
        if (seconds > 0)
        {
            this->speedY = -abs(this->speedY + this->gravityAcceleration * seconds) * 0.8;
            // std::cout << this->speedY + this->gravityAcceleration * this->clockY.getElapsedTime().asMilliseconds() << '\n';
            if (abs(this->speedY) < dj::minObjectSpeedY)
            {
                this->speedY = 0;
                this->gravityAcceleration = 0;
            }
        }
    }
    else this->gravityAcceleration = dj::gravityAcceleration;

    for (auto event : events)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                this->updateBasePosX();
                this->speedX--;
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                this->updateBasePosX();
                this->speedX++;
            }
            else if (event.key.code == sf::Keyboard::Space)
            {
                this->updateBasePosY();
                this->speedY -= 3;
            }
        }
    }

    int textureIndex = int(4 * this->getPosition().x / this->ballCircleLength) % this->textures.size();
    std::cout << textureIndex << '\n';
    this->setTexture(*this->textures[textureIndex]);
}