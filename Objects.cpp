#include "Objects.hpp"
#include "App.hpp"
#include <iostream>
#include <math.h>


void dj::Sprite::onIntersect(dj::Sprite *IntersectedSprite, const sf::FloatRect &intersection) {};
void dj::Sprite::tick(std::vector<sf::Event> events, App &app) {};
float dj::MovebleSprite::getRealPosX()
{
    // double resistanceX = this->resistanceX;
    // if (this->speedX * this->resistanceX > 0)
    //     resistanceX *= -1;
    // else if (this->speedX == 0)
    //     resistanceX = 0;
    // double realPosition = this->baseX + this->clockX.getElapsedTime().asMilliseconds() *
    //                                         (this->speedX + resistanceX * this->clockX.getElapsedTime().asMilliseconds() / 2);
    // if (abs(resistanceX * this->clockX.getElapsedTime().asMilliseconds()) >= abs(this->speedX) && this->speedX != 0)
    // {
    //     this->speedX = 0;
    //     this->baseX = realPosition;
    //     this->clockX.restart();
    // }
    // return realPosition;
    return this->basePos.x + this->speed.x * clockX.getElapsedTime().asMilliseconds();
}

float dj::MovebleSprite::getRealPosY()
{
    int clockYElapsedMiliseconds = clockY.getElapsedTime().asMilliseconds();
    return (this->basePos.y + (this->speed.y + this->gravityAcceleration * clockYElapsedMiliseconds / 2) * clockYElapsedMiliseconds);
}
int dj::MovebleSprite::updateBasePosX()
{
    // if (this->clockX.getElapsedTime().asMilliseconds() < dj::minBaseCoordinatesUpdateInterval)
    //     return -1;
    this->basePos.x = this->getPosition().x;
    return this->clockX.restart().asMilliseconds();
}
int dj::MovebleSprite::updateBasePosY()
{
    // if (this->clockY.getElapsedTime().asMilliseconds() < dj::minBaseCoordinatesUpdateInterval)
    //     return -1;
    this->basePos.y = this->getPosition().y;
    return this->clockY.restart().asMilliseconds();
}
float dj::MovebleSprite::getRealSpeedY()
{
    return this->speed.y + this->gravityAcceleration * clockY.getElapsedTime().asMilliseconds();
}

// void dj::MovebleSprite::processIntersection(dj::Sprite *intersectedSprite, const sf::FloatRect &intersection) 
// {
//     sf::FloatRect globalBoundsRect = this->getGlobalBounds();
//     this->leftBlock = intersection.left == globalBoundsRect.left;
//     this->rightBlock = (intersection.left + intersection.width) == (globalBoundsRect.left + globalBoundsRect.width);
//     this->topBlock = intersection.top == globalBoundsRect.top;
//     if (intersection.top == intersectedSprite->getGlobalBounds().top) {
//         std::cout << -intersection.height + std::nextafter(0.f, 1.f) << '\n';
//         this->move(0, -intersection.height + 1);
//         if (this->getRealSpeedY() > 0) {
//             this->updateBasePosY();
//             this->gravityAcceleration = 0;
//             this->speed.y = 0;
//         }
//     }
//     else if (this->getRealSpeedY() == 0) {
//         this->updateBasePosY();
//         this->gravityAcceleration = dj::GRAVITY_ACCELERATION;
//     }
    
//     // std::cout << (intersection.top + intersection.height) << ' '  << (globalBoundsRect.top + globalBoundsRect.height) << ' ' <<  bottomBlock << ' ' << "intersection\n";
// }

void dj::MovebleSprite::tick(std::vector<sf::Event> events, App &app)
{
    for (auto event : events)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                this->updateBasePosX();
                this->speed.x = -1;
            }
            if (event.key.code == sf::Keyboard::Right)
            {
                this->updateBasePosX();
                this->speed.x = 1;
            }
            if (event.key.code == sf::Keyboard::Space && this->getRealSpeedY() == 0)
            {
                this->updateBasePosY();
                this->speed.y = -2;
                this->gravityAcceleration = dj::GRAVITY_ACCELERATION;
            }
        }
    }
    sf::Vector2f newPos(
        this->getRealPosX(), 
        this->getRealPosY()
    );
    this->setPosition(newPos);
}

void dj::MainBallSprite::tick(std::vector<sf::Event> events, App &app)
{
    this->dj::MovebleSprite::tick(events, app);
    int textureIndex = int(this->textures.size() * this->getPosition().x / this->ballCircleLength) % this->textures.size();
    this->setTexture(*this->textures[textureIndex]);
}