#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "App.hpp"
#include "Objects.hpp"

class CrazyBallApp : public App
{
private:
    sf::Texture background_texture;
    sf::Sprite background_sprite;
    dj::MovebleSprite *focusSprite;
    sf::FloatRect viewRect = sf::FloatRect(0, 0, 1600, 1200);

public:
    CrazyBallApp(sf::RenderWindow *window)
    {
        this->window = window;
        dj::MainBallSprite ball;
        static sf::Texture texture;
        texture.loadFromFile("./images/floor_block.png");
        for (int i = 0; i < 10; i++)
        {
            dj::Sprite *floor = new dj::Sprite;
            floor->setTexture(texture);
            floor->move(i * 80, 600);
            this->staticSprites.push_back(floor);
        }
        for (int i = 0; i < 10; i++)
        {
            dj::Sprite *floor = new dj::Sprite;
            floor->setTexture(texture);
            floor->move(i * 80, 200);
            this->staticSprites.push_back(floor);
        }
        for (int i = 0; i < 10; i++)
        {
            dj::Sprite *floor = new dj::Sprite;
            floor->setTexture(texture);
            floor->move(1200 + i * 80, 200);
            this->staticSprites.push_back(floor);
        }
        for (int i = 0; i < 10; i++)
        {
            dj::Sprite *floor = new dj::Sprite;
            floor->setTexture(texture);
            floor->move(1200 + i * 80, 600);
            this->staticSprites.push_back(floor);
        }
        this->focusSprite = new dj::MainBallSprite;
        this->movebleSprites.push_back(focusSprite);
        this->background_texture.loadFromFile("./images/background.png");
        this->background_texture.setRepeated(true);
        this->background_sprite.setTexture(this->background_texture);
        this->background_sprite.setTextureRect(sf::IntRect(0, 0, 100000, 100000));
        this->background_sprite.move(-this->background_sprite.getGlobalBounds().width / 2, -this->background_sprite.getGlobalBounds().height / 2);
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
            animationIterator->tick(eventsVector, *this);
            this->window->draw(*animationIterator);
        }
        sf::FloatRect focusSpriteBounds = this->focusSprite->getGlobalBounds();
        float gaps = 100;
        float leftDistance = focusSpriteBounds.left - this->viewRect.left;
        float rightDistance = this->viewRect.left + this->viewRect.width - focusSpriteBounds.left - focusSpriteBounds.width;
        if (rightDistance < gaps)
        {
            this->viewRect.left += gaps - rightDistance;
        }
        if (leftDistance < gaps)
        {
            this->viewRect.left -= gaps - leftDistance;
        }
        sf::View newView = this->window->getView();
        newView.reset(this->viewRect);
        this->window->setView(newView);
        this->window->display();
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    CrazyBallApp app(&window);
    while (window.isOpen())
    {
        app.draw();
    }
    return 0;
}