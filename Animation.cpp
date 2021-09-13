#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include <iostream>


const sf::Drawable* Animation::get_drawable() {
    return this->drawable;
}

void Animation::tick(std::vector<sf::Event> events) {
    std::cout << "tick\n";
}