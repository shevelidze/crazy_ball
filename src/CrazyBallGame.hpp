#pragma once


#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.hpp"
#include "Sprite.hpp"
#include "MainBallSprite.hpp"
#include "MovebleSprite.hpp"
#include "FloorBlockSprite.hpp"

namespace cbg
{
    class CrazyBallGame : public Game
    {
    private:
        sf::Texture background_texture;
        sf::Sprite background_sprite;
        MovebleSprite *focusSprite;
        sf::FloatRect viewRect = sf::FloatRect(0, 0, 1600, 1200);
        sf::RenderWindow *window;

    public:
        CrazyBallGame(sf::RenderWindow *window);
        const sf::RenderWindow &get_window();
        void draw();
    };
}