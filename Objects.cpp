#include "Objects.hpp"
#include "App.hpp"
#include <iostream>

void dj::Sprite::tick(std::vector<sf::Event> events, App &app){};
float dj::MovebleSprite::getRealPosX()
{
    return this->basePos.x + this->speed.x * clockX.getElapsedTime().asMilliseconds();
}
float dj::MovebleSprite::getRealPosX(int timeMiliseconds)
{
    return this->basePos.x + this->speed.x * timeMiliseconds;
}

float dj::MovebleSprite::getRealPosY()
{
    int clockYElapsedMiliseconds = clockY.getElapsedTime().asMilliseconds();
    return (this->basePos.y + (this->speed.y + this->gravityAcceleration * clockYElapsedMiliseconds / 2) * clockYElapsedMiliseconds);
}
float dj::MovebleSprite::getRealPosY(int timeMiliseconds)
{
    return (this->basePos.y + (this->speed.y + this->gravityAcceleration * timeMiliseconds / 2) * timeMiliseconds);
}
int dj::MovebleSprite::updateBasePosX()
{
    this->basePos.x = this->getPosition().x;
    return this->clockX.restart().asMilliseconds();
}
int dj::MovebleSprite::updateBasePosY()
{
    this->basePos.y = this->getPosition().y;
    return this->clockY.restart().asMilliseconds();
}
float dj::MovebleSprite::getRealSpeedY()
{
    return this->speed.y + this->gravityAcceleration * clockY.getElapsedTime().asMilliseconds();
}

bool dj::MovebleSprite::intersectsSprites(const std::vector<dj::Sprite *> &sprites)
{
    bool intersects = false;
    for (auto spriteIterator : sprites)
        intersects = intersects || this->getGlobalBounds().intersects(spriteIterator->getGlobalBounds());
    return intersects;
}

bool dj::MovebleSprite::intersectsSprites(const sf::FloatRect &bounds, const std::vector<dj::Sprite *> &sprites)
{
    bool intersects = false;
    for (auto spriteIterator : sprites)
        intersects = intersects || bounds.intersects(spriteIterator->getGlobalBounds());
    return intersects;
}

void dj::MovebleSprite::tick(std::vector<sf::Event> events, App &app)
{
    sf::Vector2f newPos(
        this->getRealPosX(),
        this->getRealPosY());
    this->setPosition(newPos);
    bool intersected = false;
    int timeX = this->clockX.getElapsedTime().asMilliseconds();
    int timeY = this->clockY.getElapsedTime().asMilliseconds();
    float minDistance = 3;
    while (this->intersectsSprites(app.staticSprites))
    {
        intersected = true;
        --timeX;
        --timeY;
        this->setPosition(this->getRealPosX(timeX), this->getRealPosY(timeY));
    }
    if (intersected)
    {
        this->basePos.x += this->getPosition().x - this->getRealPosX();
        this->basePos.y += this->getPosition().y - this->getRealPosY();
    }
    bool topBlock = false, bottomBlock = false, leftBlock = false, rightBlock = false;
    for (auto spriteIterator : app.staticSprites)
    {
        sf::FloatRect bounds = this->getGlobalBounds();
        // std::cout << bounds.left << ' ';
        bounds.left += minDistance;
        // std::cout << bounds.left << '\n';
        if (this->intersectsSprites(bounds, app.staticSprites) && this->speed.x >= 0)
            rightBlock = true;
        bounds.left -= minDistance * 2;
        if (this->intersectsSprites(bounds, app.staticSprites) && this->speed.x <= 0)
            leftBlock = true;
        bounds.left += minDistance;
        bounds.top += minDistance;
        if (this->intersectsSprites(bounds, app.staticSprites) && this->getRealSpeedY() >= 0)
            bottomBlock = true;
        bounds.top -= minDistance * 2;
        if (this->intersectsSprites(bounds, app.staticSprites) && this->getRealSpeedY() <= 0 && !(this->gravityAcceleration > 0 && this->speed.y >= 0))
            topBlock = true;
    }
    if (bottomBlock)
    {
        this->updateBasePosY();
        this->gravityAcceleration = 0;
        this->speed.y = 0;
    }
    else if (this->bottomBlock)
    {
        this->updateBasePosY();
        this->gravityAcceleration = dj::GRAVITY_ACCELERATION;
    }
    if (topBlock)
    {
        this->updateBasePosY();
        this->speed.y = 0;
    }
    if (leftBlock)
    {
        this->updateBasePosX();
        this->speed.x = 0;
    }
    if (rightBlock)
    {
        this->updateBasePosX();
        this->speed.x = 0;
    }
    for (auto event : events)
    {
        this->leftPressed = ((event.key.code == sf::Keyboard::Left && event.type == sf::Event::KeyPressed) || this->leftPressed) &&
                            !(event.key.code == sf::Keyboard::Left && event.type == sf::Event::KeyReleased);
        this->rightPressed = ((event.key.code == sf::Keyboard::Right && event.type == sf::Event::KeyPressed) || this->rightPressed) &&
                             !(event.key.code == sf::Keyboard::Right && event.type == sf::Event::KeyReleased);
        this->spacePressed = ((event.key.code == sf::Keyboard::Space && event.type == sf::Event::KeyPressed) || this->spacePressed) &&
                             !(event.key.code == sf::Keyboard::Space && event.type == sf::Event::KeyReleased);
    }
    if (this->leftPressed && this->speed.x != -1)
    {
        this->updateBasePosX();
        this->speed.x = -1;
    }
    if (this->rightPressed && this->speed.x != 1)
    {
        this->updateBasePosX();
        this->speed.x = 1;
    }
    if (!this->spacePressed)
        this->spacePressedSinceJump = false;
    if (this->spacePressed && this->speed.y != -2)
    {
        this->updateBasePosY();
        this->speed.y = -2;
        this->gravityAcceleration = dj::GRAVITY_ACCELERATION;
        this->doubleJumpIsAvailable = true;
        this->spacePressedSinceJump = true;
    }
    else if (this->spacePressed && this->doubleJumpIsAvailable && !this->spacePressedSinceJump)
    {
        this->updateBasePosY();
        this->doubleJumpIsAvailable = false;
    }
    this->bottomBlock = bottomBlock;
    this->topBlock = topBlock;
    this->leftBlock = leftBlock;
    this->rightBlock = rightBlock;
}

void dj::MainBallSprite::tick(std::vector<sf::Event> events, App &app)
{
    this->dj::MovebleSprite::tick(events, app);
    int textureIndex = int(this->textures.size() * this->getPosition().x / this->ballCircleLength) % this->textures.size();
    this->setTexture(*this->textures[textureIndex]);
}