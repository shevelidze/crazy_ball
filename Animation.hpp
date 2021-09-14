#ifndef ANIMATION_H
#define ANIMATION_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


class App;

class Animation
{
protected:
	sf::Drawable *drawable;
public:
	virtual void tick(std::vector<sf::Event> events, App& app) = 0;
	virtual const sf::Drawable* get_drawable() = 0;
};
#endif