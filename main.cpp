#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Animation.hpp"
#include "SunAnimation.hpp"

class DoodleJumpApp
{
private:
    sf::RenderWindow *window;
    std::vector<Animation*> animations;

public:
    DoodleJumpApp(sf::RenderWindow *window)
    {
        this->window = window;
        this->animations.push_back(new SunAnimation);
    }
    void draw()
    {
        this->window->clear();
        sf::Event event;
        std::vector<sf::Event> eventsVector;
        while (this->window->pollEvent(event)) eventsVector.push_back(event);
        for (auto animation_iterator : this->animations)
        {
            animation_iterator->tick(eventsVector);
            this->window->draw(*animation_iterator->get_drawable());
        }
        this->window->display();
    }
};

main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    DoodleJumpApp app(&window);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        app.draw();
    }
    return 0;
}