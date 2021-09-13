#ifndef ANIMATION_H
#define ANIMATION_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
private:
	sf::Drawable *drawable;
public:
	Animation()
	{
		this->drawable = new sf::CircleShape(100.f);
	}
	void tick(std::vector<sf::Event> events);
	const sf::Drawable* get_drawable();
};
#endif