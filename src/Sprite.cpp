#include "Sprite.hpp"

namespace cbg
{
    void Sprite::tick(std::vector<sf::Event> events, CrazyBallGame &app){};
    void Sprite::onIntersect(MovebleSprite *movebleSprite, const Side &side){};
}