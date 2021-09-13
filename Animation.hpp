#ifndef ANIMATION_H
#define ANIMATION_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
protected:
	sf::Drawable *drawable;
public:
	Animation()
	{
		this->drawable = new sf::CircleShape(100.f);
	}
	virtual void tick(std::vector<sf::Event> events);
	virtual const sf::Drawable* get_drawable();
};
#endif