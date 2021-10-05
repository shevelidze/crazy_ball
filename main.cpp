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
        static sf::Texture texture;
        texture.loadFromFile("./images/floor_block.png");
        for (int i=0; i<10; i++) {
            dj::Sprite *floor = new dj::Sprite;
            floor->setTexture(texture);
            floor->move(i*80, 600);
            this->staticSprites.push_back(floor);
        }
        for (int i=0; i<10; i++) {
            dj::Sprite *floor = new dj::Sprite;
            floor->setTexture(texture);
            floor->move(1200 + i*80, 600);
            this->staticSprites.push_back(floor);
        }
        this->movebleSprites.push_back(new dj::MainBallSprite);
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
            for (auto checkAnimationIterator : this->staticSprites)
            {
                sf::FloatRect intersection;
                bool intersects = animationIterator->getGlobalBounds().intersects(checkAnimationIterator->getGlobalBounds(), intersection);
                if (intersects && intersection.top == checkAnimationIterator->getGlobalBounds().top)
                {
                    animationIterator->move(0, -intersection.height + 1);
                    if (animationIterator->getRealSpeedY() > 0)
                    {
                        animationIterator->updateBasePosY();
                        animationIterator->gravityAcceleration = 0;
                        animationIterator->speed.y = 0;
                    }
                }
                else if (animationIterator->gravityAcceleration == 0)
                {
                    animationIterator->updateBasePosY();
                    animationIterator->gravityAcceleration = dj::GRAVITY_ACCELERATION;
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
    DoodleJumpApp app(&window);
    while (window.isOpen())
    {
        app.draw();
    }
    return 0;
}