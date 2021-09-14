#include <iostream>
#include "SunAnimation.hpp"
#include <string>
#include <cmath>

SunAnimation::SunAnimation()
{
    sf::Sprite sprite;
    std::vector<sf::Texture *> textures;
    for (int i = 0; i < 5; i++)
    {
        sf::Texture *tempTexture = new sf::Texture;
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

void SunAnimation::updateSpritePosition()
{
    // std::cout << this->speed << this->horisontalSpeed << '\n';
    this->sprite.setPosition(
        this->baseX + this->horisontalSpeed * this->xClock.getElapsedTime().asMilliseconds(),
        this->baseY + this->yClock.getElapsedTime().asMilliseconds() * (this->speed + this->gravitationalAcceleration * this->yClock.getElapsedTime().asMilliseconds()));
}

void SunAnimation::tick(std::vector<sf::Event> events, App &app)
{
    // this->current_frame ++;
    // if (this->current_frame >= this->textures.size()) this->current_frame = 0;
    // sprite.setTexture(*textures[this->current_frame]);
    std::cout << events.size() << '\n';
    for (auto event : events)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                this->horisontalSpeed --;
                this->baseX = this->sprite.getPosition().x;
                this->xClock.restart();
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                this->horisontalSpeed ++;
                this->baseX = this->sprite.getPosition().x;
                this->xClock.restart();
            }
        }
    }
    updateSpritePosition();
    double departure = this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height - app.get_window().getSize().y;
    if (departure >= 0)
    {
        this->baseY = this->sprite.getPosition().y;
        this->sprite.move(0, -departure);
        this->speed = (this->speed + this->gravitationalAcceleration * this->yClock.getElapsedTime().asMilliseconds()) * -0.8;
        if (this->speed > -1)
            this->speed = -1;
        this->yClock.restart();
        updateSpritePosition();
    }
}

const sf::Drawable *SunAnimation::get_drawable()
{
    return &this->sprite;
}