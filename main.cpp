#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Animation.hpp"
#include "SunAnimation.hpp"
#include "App.hpp"

class DoodleJumpApp : public App
{
private:
    std::vector<Animation *> animations;

public:
    DoodleJumpApp(sf::RenderWindow* window)
    {
        this->window = window;
        this->animations.push_back(new SunAnimation);
    }
    const sf::RenderWindow& get_window() {
        return *this->window;
    }
    void draw()
    {
        this->window->clear();
        sf::Event event;
        std::vector<sf::Event> eventsVector;
        while (this->window->pollEvent(event))
            eventsVector.push_back(event);
            if (event.type == sf::Event::Closed)
                this->window->close();
        for (auto animation_iterator : this->animations)
        {
            animation_iterator->tick(eventsVector, *this);
            this->window->draw(*animation_iterator->get_drawable());
        }
        this->window->display();
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
    DoodleJumpApp app(&window);
    // window.setFramerateLimit(60);
    while (window.isOpen())
    {
        app.draw();
    }
    return 0;
}