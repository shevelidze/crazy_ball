#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class App;

namespace dj
{
    const double GRAVITY_ACCELERATION = 0.032 / 5;
    const int minBaseCoordinatesUpdateInterval = 100;
    const double minObjectSpeedY = dj::GRAVITY_ACCELERATION * 50;

    class Sprite : public sf::Sprite
    {
    public:
        virtual void tick(std::vector<sf::Event> events, App &app);
        virtual void onIntersect(dj::Sprite *intersectedSprite, const sf::FloatRect &intersection); // calling before tick
    };
    class MovebleSprite : public dj::Sprite
    {
    private:
        sf::Vector2f basePos;
        sf::Clock clockX;
        sf::Clock clockY;

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