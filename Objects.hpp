#pragma once

#include <SFML/Graphics.hpp>

class App;

namespace dj
{
    const double gravityAcceleration = 0.032 / 5;
    const int minBaseCoordinatesUpdateInterval = 100;
    const double minObjectSpeedY = dj::gravityAcceleration * 50;

    class Sprite : public sf::Sprite
    {
    private:
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
        void tick(std::vector<sf::Event> events, App &app);
        bool gravityOperates = false;
        bool isLeftTransparent = false;
        bool isRightTransparent = false;
        bool isTopTransparent = false;
        bool isBottomTransparent = false;
        Sprite() {
            sf::Texture *texture = new sf::Texture;
            texture->loadFromFile("./sun/frame_0.png");
            this->setTexture(*texture);
        }
    };
};