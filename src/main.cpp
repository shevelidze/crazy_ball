#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "CrazyBallGame.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    cbg::CrazyBallGame app(&window);
    while (window.isOpen())
    {
        app.draw();
    }
    return 0;
}