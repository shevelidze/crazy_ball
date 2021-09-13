#ifndef SUNANIMATION_H
#define SUNANIMATION_H
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"

class SunAnimation : Animation
{
private:


public:
	SunAnimation();
	~SunAnimation();
	void tick(std::vector<sf::Event> events);
};
#endif