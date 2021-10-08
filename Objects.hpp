#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class App;

namespace dj
{
    const double GRAVITY_ACCELERATION = 0.032 / 5;
    const double minObjectSpeedY = dj::GRAVITY_ACCELERATION * 50;

    class Sprite : public sf::Sprite
    {
    public:
        virtual void tick(std::vector<sf::Event> events, App &app);
    };
    class MovebleSprite : public dj::Sprite
    {
    private:
        sf::Vector2f basePos;
        sf::Vector2f previousPos;
        sf::Clock clockX;
        sf::Clock clockY;
        bool intersectsSprites(const std::vector<dj::Sprite *> &sprites);
        bool intersectsSprites(const sf::FloatRect &bounds, const std::vector<dj::Sprite *> &sprites);

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
};