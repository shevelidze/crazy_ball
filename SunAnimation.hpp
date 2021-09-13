#ifndef SUNANIMATION_H
#define SUNANIMATION_H
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"

class SunAnimation : public Animation
{
private:
	sf::Sprite sprite;
	std::vector<sf::Texture*> textures;
	int current_frame = 0;

public:
	SunAnimation();
	~SunAnimation();
	void tick(std::vector<sf::Event> events);
	const sf::Drawable* get_drawable();
};
#endif