#ifndef APP_H
#define APP_H
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

class App
{
protected:
	sf::RenderWindow* window;
	// std::vector<Animation *> animations;

public:
	virtual const sf::RenderWindow& get_window() = 0;
	App();
	~App();
};
#endif