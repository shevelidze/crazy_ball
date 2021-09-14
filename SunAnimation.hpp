#ifndef SUNANIMATION_H
#define SUNANIMATION_H
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "App.hpp"

class SunAnimation : public Animation
{
private:
	sf::Sprite sprite;
	std::vector<sf::Texture*> textures;
	int current_frame = 0;
	// px per ms
	double speed = 0.5;
	double horisontalSpeed = 0;
	double gravitationalAcceleration = 0.001;
	sf::Clock xClock;
	sf::Clock yClock;
	int baseX = 0;
	int baseY = 0;
	void updateSpritePosition();
public:
	SunAnimation();
	~SunAnimation();
	void tick(std::vector<sf::Event> events, App& app);
	const sf::Drawable* get_drawable();
};
#endif