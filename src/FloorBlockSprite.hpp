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
		sf::Clock lastIntersectionClock;
		int intersection = false;
		int fadingDurationMiliseconds = 500;
		int fadingDelayMiliseconds = 100;
		bool isFading = false;
		bool isFaded = true;
		sf::Clock fadingClock;

	public:
		FloorBlockSprite();
		void onIntersect(MovebleSprite *movebleSprite, const Side &side);
		virtual void tick(std::vector<sf::Event> events, CrazyBallGame &app);
	};
}
#endif