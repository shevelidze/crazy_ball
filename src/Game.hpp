#ifndef GAME_H
#define GAME_H
#pragma once


#include <SFML/Graphics.hpp>


namespace cbg
{
	class Sprite;
	class MovebleSprite;
    class Game
    {
    public:
        std::vector<Sprite *> staticSprites;
        std::vector<MovebleSprite *> movebleSprites;
        virtual const sf::RenderWindow &get_window() = 0;
        virtual void draw() = 0;
    };
}
#endif