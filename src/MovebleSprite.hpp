#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Sprite.hpp"
#include "Game.hpp"
#include "Sides.hpp"

namespace cbg
{
    const double GRAVITY_ACCELERATION = 0.032 / 5;
    class MovebleSprite : public Sprite
    {
    private:
        sf::Vector2f basePos;
        sf::Vector2f previousPos;
        sf::Clock clockX;
        sf::Clock clockY;
        bool intersectsSprites(const std::vector<Sprite *> &sprites);
        bool intersectsSprites(const sf::FloatRect &bounds, const std::vector<Sprite *> &sprites, const Side &side);

    protected:
        bool topBlock, bottomBlock, leftBlock, rightBlock;
        bool leftPressed = false, rightPressed = false, spacePressed = false;

    public:
        float gravityAcceleration = GRAVITY_ACCELERATION;
        int updateBasePosX();
        int updateBasePosY();
        float getRealPosX();
        float getRealPosY();
        float getRealSpeedY();
        sf::Vector2f speed;
        virtual void tick(std::vector<sf::Event> events, Game &app);
        MovebleSprite() : basePos(0, 0), speed(0, 0){};
    };
}
