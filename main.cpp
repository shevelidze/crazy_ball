#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "App.hpp"
#include "Objects.hpp"

class DoodleJumpApp : public App
{
private:
    std::vector<dj::Sprite *> sprites;
    sf::Texture background_texture;
    sf::Sprite background_sprite;

public:
    DoodleJumpApp(sf::RenderWindow *window)
    {
        this->window = window;
        this->sprites.push_back(new dj::MainBallSprite);
        this->background_texture.loadFromFile("./images/background.png");
        this->background_sprite.setTexture(this->background_texture);
    }
    const sf::RenderWindow &get_window()
    {
        return *this->window;
    }
    void draw()
    {
        this->window->clear();
        sf::Event event;
        std::vector<sf::Event> eventsVector;
        while (this->window->pollEvent(event))
        {
            eventsVector.push_back(event);
            if (event.type == sf::Event::Closed)
                this->window->close();
        }
        this->window->draw(this->background_sprite);
        for (auto animation_iterator : this->sprites)
        {
            animation_iterator->tick(eventsVector, *this);
            this->window->draw(*animation_iterator);
        }
        this->window->display();
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
    // window.setFramerateLimit(144);
    DoodleJumpApp app(&window);
    // window.setFramerateLimit(60);
    while (window.isOpen())
    {
        app.draw();
    }
    return 0;
}