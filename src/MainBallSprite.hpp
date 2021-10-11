#ifndef MAINBALLSPRITE_H
#define MAINBALLSPRITE_H
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "MovebleSprite.hpp"
#include "Game.hpp"

namespace cbg
{
	class MainBallSprite : public MovebleSprite
	{
	private:
		double ballCircleLength;
		std::vector<sf::Texture *> textures;

	public:
		MainBallSprite();
		void tick(std::vector<sf::Event> events, Game &app);
	};
}


#endif