#ifndef APP_H
#define APP_H
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Objects.hpp"

class App
{
protected:
	sf::RenderWindow* window;

public:
	virtual const sf::RenderWindow& get_window() = 0;
	std::vector<dj::Sprite *> staticSprites;
    std::vector<dj::MovebleSprite *> movebleSprites;
	App();
	~App();
};
#endif