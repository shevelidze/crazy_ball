#include "Objects.hpp"
#include "App.hpp"
#include <iostream>
#include <math.h>


void dj::Sprite::tick(std::vector<sf::Event> events, App &app){};
void dj::Sprite::onIntersect(dj::MovebleSprite *movebleSprite, const dj::Side &side){};
float dj::MovebleSprite::getRealPosX()
{
    return this->basePos.x + this->speed.x * clockX.getElapsedTime().asMilliseconds();
}

float dj::MovebleSprite::getRealPosY()
{
    int clockYElapsedMiliseconds = clockY.getElapsedTime().asMilliseconds();
    return (this->basePos.y + (this->speed.y + this->gravityAcceleration * clockYElapsedMiliseconds / 2) * clockYElapsedMiliseconds);
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

bool dj::MovebleSprite::intersectsSprites(const sf::FloatRect &bounds, const std::vector<dj::Sprite *> &sprites, const dj::Side &side)
{
    bool intersects = false;
    for (auto spriteIterator : sprites)
    {
        if (bounds.intersects(spriteIterator->getGlobalBounds()))
        {
            intersects = true;
            spriteIterator->onIntersect(this, side.getInverted());
        }
    }
    return intersects;
}

void dj::MovebleSprite::tick(std::vector<sf::Event> events, App &app)
{
    sf::Vector2f newPos(
        this->getRealPosX(),
        this->getRealPosY());
    this->setPosition(newPos);
    bool intersected = this->intersectsSprites(app.staticSprites);
    bool topBlock = false, bottomBlock = false, leftBlock = false, rightBlock = false;
    if (intersected)
    {
        sf::Vector2f move = this->getPosition() - this->previousPos;
        this->setPosition(this->previousPos);
        move.x = abs(move.x);
        move.y = abs(move.y);
        sf::FloatRect checkBounds = this->getGlobalBounds();
        checkBounds.left -= move.x;
        if (this->intersectsSprites(checkBounds, app.staticSprites, dj::Sides::LEFT))
            leftBlock = true;
        checkBounds.left += move.x * 2;
        if (this->intersectsSprites(checkBounds, app.staticSprites, dj::Sides::RIGHT))
            rightBlock = true;
        checkBounds.left -= move.x;
        checkBounds.top += move.y;
        if (this->intersectsSprites(checkBounds, app.staticSprites, dj::Sides::BOTTOM))
            bottomBlock = true;
        checkBounds.top -= move.y * 2;
        if (this->intersectsSprites(checkBounds, app.staticSprites, dj::Sides::TOP))
            topBlock = true;
    }

    if (bottomBlock && !this->bottomBlock)
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
    if (topBlock && !this->topBlock)
    {
        this->updateBasePosY();
        this->speed.y = 0;
    }
    if (leftBlock && !this->leftBlock)
    {
        this->updateBasePosX();
        this->speed.x = 0;
    }
    if (rightBlock && this->rightBlock)
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
    this->bottomBlock = bottomBlock;
    this->topBlock = topBlock;
    this->leftBlock = leftBlock;
    this->rightBlock = rightBlock;
    this->previousPos = this->getPosition();
}

void dj::MainBallSprite::tick(std::vector<sf::Event> events, App &app)
{
    this->dj::MovebleSprite::tick(events, app);
    int textureIndex = int(this->textures.size() * this->getPosition().x / this->ballCircleLength) % this->textures.size();
    this->setTexture(*this->textures[textureIndex]);
    float speedX = 1.5;
    if (leftPressed && this->speed.x != -speedX && !leftBlock)
    {
        this->updateBasePosX();
        this->speed.x = -speedX;
    }
    if (rightPressed && this->speed.x != speedX && !rightBlock)
    {
        this->updateBasePosX();
        this->speed.x = speedX;
    }
    if (!(rightPressed || leftPressed) && this->speed.x != 0)
    {
        this->updateBasePosX();
        this->speed.x = 0;
    }
    if (this->spacePressed && this->speed.y != -2 && !topBlock && bottomBlock)
    {
        this->updateBasePosY();
        this->speed.y = -1.7f;
        this->gravityAcceleration = dj::GRAVITY_ACCELERATION;
    }
}