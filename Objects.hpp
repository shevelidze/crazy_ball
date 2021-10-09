#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class App;

namespace dj
{
    class MovebleSprite;
    const double GRAVITY_ACCELERATION = 0.032 / 5;
    const double minObjectSpeedY = dj::GRAVITY_ACCELERATION * 50;
    class Side
    {
    private:
        bool topBlock, rightBlock, bottomBlock, leftBlock;

    public:
        Side(const bool &topBlock, const bool &rightBlock, const bool &bottomBlock, const bool &leftBlock)
        {
            this->bottomBlock = bottomBlock;
            this->topBlock = topBlock;
            this->rightBlock = rightBlock;
            this->leftBlock = leftBlock;
        }
        bool operator==(const Side &a) const
        {
            return a.topBlock == this->topBlock &&
                   a.rightBlock == this->rightBlock &&
                   a.bottomBlock == this->bottomBlock &&
                   a.leftBlock == this->leftBlock;
        }
        bool operator!=(const Side &a) const
        {
            return !(*this == a);
        }
        Side operator=(const Side &a)
        {
            this->topBlock = a.topBlock;
            this->rightBlock = a.rightBlock;
            this->bottomBlock = a.bottomBlock;
            this->leftBlock = a.leftBlock;
            return *this;
        }
        Side getInverted() const
        {
            Side inverted = *this;
            std::swap(inverted.topBlock, inverted.bottomBlock);
            std::swap(inverted.leftBlock, inverted.rightBlock);
            return inverted;
        }
    };
    namespace Sides
    {
        const dj::Side TOP(true, false, false, false);
        const dj::Side RIGHT(false, true, false, false);
        const dj::Side BOTTOM(false, false, true, false);
        const dj::Side LEFT(false, false, false, true);
    }

    class Sprite : public sf::Sprite
    {
    public:
        virtual void tick(std::vector<sf::Event> events, App &app);
        virtual void onIntersect(dj::MovebleSprite *movebleSprite, const dj::Side &side);
    };
    class MovebleSprite : public dj::Sprite
    {
    private:
        sf::Vector2f basePos;
        sf::Vector2f previousPos;
        sf::Clock clockX;
        sf::Clock clockY;
        bool intersectsSprites(const std::vector<dj::Sprite *> &sprites);
        bool intersectsSprites(const sf::FloatRect &bounds, const std::vector<dj::Sprite *> &sprites, const dj::Side &side);

    protected:
        bool topBlock, bottomBlock, leftBlock, rightBlock;
        bool leftPressed = false, rightPressed = false, spacePressed = false;

    public:
        float gravityAcceleration = dj::GRAVITY_ACCELERATION;
        int updateBasePosX();
        int updateBasePosY();
        float getRealPosX();
        float getRealPosY();
        float getRealSpeedY();
        sf::Vector2f speed;
        virtual void tick(std::vector<sf::Event> events, App &app);
        MovebleSprite() : basePos(0, 0), speed(0, 0){};
    };

    class MainBallSprite : public dj::MovebleSprite
    {
    private:
        double ballCircleLength;
        std::vector<sf::Texture *> textures;

    public:
        MainBallSprite()
        {
            for (int i = 0; i < 8; ++i)
            {
                sf::Texture *texture = new sf::Texture;
                texture->loadFromFile("./images/ball/" + std::to_string(i) + ".png");
                this->textures.push_back(texture);
            }
            this->setTexture(*(this->textures[0]));
            this->ballCircleLength = M_PI * this->getGlobalBounds().width;
        }
        void tick(std::vector<sf::Event> events, App &app);
    };

    class floorBlockSprite : public dj::Sprite
    {
    private:
        int noTopIntersectionsTimesInRow = 0;
        int topIntersection = false;

    public:
        floorBlockSprite() : dj::Sprite()
        {
            static sf::Texture texture;
            texture.loadFromFile("./images/floor_block.png");
            this->setTexture(texture);
        }
        void onIntersect(dj::MovebleSprite *movebleSprite, const dj::Side &side)
        {
            if (side == dj::Sides::TOP || side == dj::Sides::BOTTOM)
            {
                this->topIntersection = true;
            }
        }
        virtual void tick(std::vector<sf::Event> events, App &app)
        {
            if (this->topIntersection)
            {
                this->setColor(sf::Color::Red);
                noTopIntersectionsTimesInRow = 0;
            }
            else if (noTopIntersectionsTimesInRow >= 1000)
            {
                this->setColor(sf::Color::White);
                noTopIntersectionsTimesInRow = 1001;
            }
            else
            {
                noTopIntersectionsTimesInRow++;
            }
            this->topIntersection = false;
        }
    };
};