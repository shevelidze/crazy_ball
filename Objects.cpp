#include "Objects.hpp"
#include "App.hpp"
#include <iostream>
#include <math.h>



// void dj::Sprite::checkForMinSpeedY()
// {
// }



// void dj::MainBallSprite::tick(std::vector<sf::Event> events, App &app)
// {
//     this->setPosition(this->getRealPosX(), this->getRealPosY());
//     double departure = this->getRealPosY() + this->getGlobalBounds().height - app.get_window().getSize().y;
//     if (departure >= 0)
//     {
//         int seconds = this->updateBasePosY();
//         this->setPosition(this->getRealPosX(), app.get_window().getSize().y - this->getGlobalBounds().height);
//         if (seconds > 0)
//         {
//             this->speedY = -abs(this->speedY + this->gravityAcceleration * seconds) * 0.8;
//             // std::cout << this->speedY + this->gravityAcceleration * this->clockY.getElapsedTime().asMilliseconds() << '\n';
//             if (abs(this->speedY) < dj::minObjectSpeedY)
//             {
//                 this->speedY = 0;
//                 this->gravityAcceleration = 0;
//             }
//         }
//     }
//     else this->gravityAcceleration = dj::gravityAcceleration;

//     for (auto event : events)
//     {
//         if (event.type == sf::Event::KeyPressed)
//         {
//             if (event.key.code == sf::Keyboard::Left)
//             {
//                 this->updateBasePosX();
//                 this->speedX--;
//             }
//             else if (event.key.code == sf::Keyboard::Right)
//             {
//                 this->updateBasePosX();
//                 this->speedX++;
//             }
//             else if (event.key.code == sf::Keyboard::Space)
//             {
//                 this->updateBasePosY();
//                 this->speedY -= 3;
//             }
//         }
//     }

//     int textureIndex = int(4 * this->getPosition().x / this->ballCircleLength) % this->textures.size();
//     std::cout << textureIndex << '\n';
//     this->setTexture(*this->textures[textureIndex]);
// }
// void dj::MainBallSprite::tick(std::vector<sf::Event> events, App &app)
// {
//     this->setPosition(this->getRealPosX(), this->getRealPosY());
//     double departure = this->getRealPosY() + this->getGlobalBounds().height - app.get_window().getSize().y;
//     if (departure >= 0)
//     {
//         int seconds = this->updateBasePosY();
//         this->setPosition(this->getRealPosX(), app.get_window().getSize().y - this->getGlobalBounds().height);
//         if (seconds > 0)
//         {
//             this->speedY = -abs(this->speedY + this->gravityAcceleration * seconds) * 0.8;
//             // std::cout << this->speedY + this->gravityAcceleration * this->clockY.getElapsedTime().asMilliseconds() << '\n';
//             if (abs(this->speedY) < dj::minObjectSpeedY)
//             {
//                 this->speedY = 0;
//                 this->gravityAcceleration = 0;
//             }
//         }
//     }
//     else this->gravityAcceleration = dj::gravityAcceleration;

//     for (auto event : events)
//     {
//         if (event.type == sf::Event::KeyPressed)
//         {
//             if (event.key.code == sf::Keyboard::Left)
//             {
//                 this->updateBasePosX();
//                 this->speedX--;
//             }
//             else if (event.key.code == sf::Keyboard::Right)
//             {
//                 this->updateBasePosX();
//                 this->speedX++;
//             }
//             else if (event.key.code == sf::Keyboard::Space)
//             {
//                 this->updateBasePosY();
//                 this->speedY -= 3;
//             }
//         }
//     }

//     int textureIndex = int(4 * this->getPosition().x / this->ballCircleLength) % this->textures.size();
//     std::cout << textureIndex << '\n';
//     this->setTexture(*this->textures[textureIndex]);
// }

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
    this->basePos.x = this->getRealPosX();
    return this->clockX.restart().asMilliseconds();
}
int dj::MovebleSprite::updateBasePosY()
{
    // if (this->clockY.getElapsedTime().asMilliseconds() < dj::minBaseCoordinatesUpdateInterval)
    //     return -1;
    this->basePos.y = this->getRealPosY();
    return this->clockY.restart().asMilliseconds();
}
float dj::MovebleSprite::getRealSpeedY()
{
    return this->speed.y + this->gravityAcceleration * clockY.getElapsedTime().asMilliseconds();
}

void dj::MovebleSprite::onIntersect(dj::Sprite *intersectedSprite, const sf::FloatRect &intersection) 
{
    sf::FloatRect globalBoundsRect = this->getGlobalBounds();
    this->leftBlock = intersection.left == globalBoundsRect.left;
    this->rightBlock = (intersection.left + intersection.width) == (globalBoundsRect.left + globalBoundsRect.width);
    this->topBlock = intersection.top == globalBoundsRect.top;
    this->bottomBlock = intersection.top == intersectedSprite->getGlobalBounds().top;
    // std::cout << (intersection.top + intersection.height) << ' '  << (globalBoundsRect.top + globalBoundsRect.height) << ' ' <<  bottomBlock << ' ' << "intersection\n";
}

void dj::MovebleSprite::tick(std::vector<sf::Event> events, App &app)
{
    // std::cout << this->clockX.getElapsedTime().asMilliseconds() << '\n';
    if (this->getRealSpeedY() > 0 && this->bottomBlock) {
        this->updateBasePosY();
        this->gravityAcceleration = 0;
        this->speed.y = 0;
    }
    if (this->getRealSpeedY() == 0 && !this->bottomBlock) 
    {
        this->updateBasePosY();
        this->gravityAcceleration = dj::GRAVITY_ACCELERATION;
    }
    if (this->getRealSpeedY() < 0 && this->topBlock) {
        this->updateBasePosY();
        this->speed.y = 0;
    }
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
    int textureIndex = int(4 * this->getPosition().x / this->ballCircleLength) % this->textures.size();
    this->setTexture(*this->textures[textureIndex]);
}