#ifndef SPRITE_H
#define SPRITE_H
#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include "Side.hpp"


namespace cbg
{
	class CrazyBallGame;
	class MovebleSprite;
	class Sprite : public sf::Sprite
	{
	public:
		virtual void tick(std::vector<sf::Event> events, CrazyBallGame &app);
		virtual void onIntersect(MovebleSprite *movebleSprite, const Side &side);
	};

}
#endif