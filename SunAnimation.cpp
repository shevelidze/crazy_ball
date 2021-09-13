#include <iostream>
#include "SunAnimation.hpp"
#include <string>
	
SunAnimation::SunAnimation()
{
    sf::Sprite sprite;
    std::vector<sf::Texture*> textures;
    for (int i=0; i<5; i++) {
        sf::Texture* tempTexture = new sf::Texture;
        tempTexture->loadFromFile("./sun/frame_" + std::to_string(i) + ".png");
        textures.push_back(tempTexture);
    }
    sprite.setTexture(*textures[this->current_frame]);
    this->sprite = sprite;
    this->textures = textures;
}
	
SunAnimation::~SunAnimation()
{
	
}

void SunAnimation::tick(std::vector<sf::Event> events) {
    this->current_frame ++;
    if (this->current_frame >= this->textures.size()) this->current_frame = 0;
    sprite.setTexture(*textures[this->current_frame]);
}

const sf::Drawable* SunAnimation::get_drawable() {
    return &this->sprite;
}