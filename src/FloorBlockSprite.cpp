#include "FloorBlockSprite.hpp"
#include <iostream>

namespace cbg
{
    FloorBlockSprite::FloorBlockSprite() : Sprite()
    {
        static sf::Texture texture;
        texture.loadFromFile("./images/floor_block.png");
        this->setTexture(texture);
    }
    void FloorBlockSprite::tick(std::vector<sf::Event> events, CrazyBallGame &app)
    {
        sf::Color newColor = this->getColor();
        if (this->intersection)
        {
            newColor = sf::Color::Red;
            this->lastIntersectionClock.restart();
            this->isFaded = false;
            this->isFading = false;
        }
        else if (this->lastIntersectionClock.getElapsedTime().asMilliseconds() > this->fadingDelayMiliseconds && !this->isFading && !this->isFaded)
        {
            this->isFading = true;
            this->fadingClock.restart();
        }

        if (this->isFading)
        {
            int chanelsValue = (double(this->fadingClock.getElapsedTime().asMilliseconds()) / this->fadingDurationMiliseconds) * 255;
            std::cout << chanelsValue << '\n';
            if (chanelsValue >= 255) {
                newColor = sf::Color::White;
                this->isFading = false;
                this->isFaded = true;
            }
            else {
                newColor.g = newColor.b = chanelsValue;
            }
        }

        this->setColor(newColor);

        this->intersection = false;
    }
    void FloorBlockSprite::onIntersect(MovebleSprite *movebleSprite, const Side &side)
    {
        this->intersection = true;
    }
}