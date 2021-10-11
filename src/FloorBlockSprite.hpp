#ifndef FLOORBLOCKSPRITE_H
#define FLOORBLOCKSPRITE_H
#pragma once

#include <SFML/Graphics.hpp>
#include "Sprite.hpp"
#include "Side.hpp"
#include "MovebleSprite.hpp"


namespace cbg
{
	class FloorBlockSprite : public Sprite
	{
	private:
		int noTopIntersectionsTimesInRow = 0;
		int topIntersection = false;

	public:
		FloorBlockSprite();
		void onIntersect(MovebleSprite *movebleSprite, const Side &side);
		virtual void tick(std::vector<sf::Event> events, CrazyBallGame &app);
	};
}
#endif