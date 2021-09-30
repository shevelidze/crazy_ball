#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class App;

namespace dj
{
    const double gravityAcceleration = 0.032 / 5;
    const int minBaseCoordinatesUpdateInterval = 100;
    const double minObjectSpeedY = dj::gravityAcceleration * 50;

    class Sprite : public sf::Sprite
    {
    protected:
        double gravityAcceleration = dj::gravityAcceleration;
        double baseX = 0;
        double baseY = 0;
        double speedX = 0;
        double speedY = 0;
        double resistanceX = 0.001;
        sf::Clock clockX;
        sf::Clock clockY;
        double getRealPosX();
        double getRealPosY();
        int updateBasePosX();
        int updateBasePosY();
        void checkForMinSpeedY();

    public:
        virtual void tick(std::vector<sf::Event> events, App &app) = 0;
        bool gravityOperates = false;
        bool isLeftTransparent = false;
        bool isRightTransparent = false;
        bool isTopTransparent = false;
        bool isBottomTransparent = false;
        Sprite() {
            // sf::Texture *texture = new sf::Texture;
            // texture->loadFromFile("./images/ball/1.png");
            // this->setTexture(*texture);
        }
    };

    class MainBallSprite : public dj::Sprite {
    private:
        double ballCircleLength;
        std::vector<sf::Texture *> textures;
    public:
        MainBallSprite() {
            for (int i=0; i<4; ++i) {
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