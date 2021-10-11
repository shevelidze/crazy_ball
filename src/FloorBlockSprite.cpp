#include "FloorBlockSprite.hpp"

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
    void FloorBlockSprite::onIntersect(MovebleSprite *movebleSprite, const Side &side)
    {
        if (side == Sides::TOP || side == Sides::BOTTOM)
        {
            this->topIntersection = true;
        }
    }
}