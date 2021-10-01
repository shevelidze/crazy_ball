#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "App.hpp"
#include "Objects.hpp"

class DoodleJumpApp : public App
{
private:
    std::vector<dj::Sprite *> staticSprites;
    std::vector<dj::MovebleSprite *> movebleSprites;
    sf::Texture background_texture;
    sf::Sprite background_sprite;

public:
    DoodleJumpApp(sf::RenderWindow *window)
    {
        this->window = window;
        dj::MainBallSprite ball;
        std::cout << ball.getGlobalBounds().height << ' ' << ball.getGlobalBounds().width << '\n';
        dj::Sprite *floor = new dj::Sprite;
        static sf::Texture texture;
        texture.loadFromFile("./images/tree.png");
        floor->setTexture(texture);
        floor->move(200, 600);
        std::cout << floor->getGlobalBounds().height << ' ' << floor->getGlobalBounds().width << '\n';


        this->movebleSprites.push_back(new dj::MainBallSprite);
        this->staticSprites.push_back(floor);
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
        for (auto animationIterator : this->staticSprites)
        {
            animationIterator->tick(eventsVector, *this);
            this->window->draw(*animationIterator);
        }
        for (auto animationIterator : this->movebleSprites)
        {
            animationIterator->resetBlocks();
            for (auto checkAnimationIterator : this->staticSprites)
            {
                sf::FloatRect intersection;
                bool intersects = animationIterator->getGlobalBounds().intersects(checkAnimationIterator->getGlobalBounds(), intersection);
                if (intersects) {
                    animationIterator->onIntersect(checkAnimationIterator, intersection);
                }
            }
            animationIterator->tick(eventsVector, *this);
            this->window->draw(*animationIterator);
        }
        this->window->display();
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
    // window.setFramerateLimit(144);
    DoodleJumpApp app(&window);
    while (window.isOpen())
    {
        app.draw();
    }
    return 0;
}