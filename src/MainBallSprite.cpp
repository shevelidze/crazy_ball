#include "MainBallSprite.hpp"


namespace cbg
{
    MainBallSprite::MainBallSprite()
    {
        for (int i = 0; i < 8; ++i)
        {
            sf::Texture *texture = new sf::Texture;
            texture->loadFromFile("./images/ball/" + std::to_string(i) + ".png");
            this->textures.push_back(texture);
        }
        this->setTexture(*(this->textures[0]));
        this->ballCircleLength = M_PI * this->getGlobalBounds().width;
    }
    void MainBallSprite::tick(std::vector<sf::Event> events, Game &app)
    {
        this->MovebleSprite::tick(events, app);
        int textureIndex = int(this->textures.size() * this->getPosition().x / this->ballCircleLength) % this->textures.size();
        this->setTexture(*this->textures[textureIndex]);
        float speedX = 1.5;
        if (leftPressed && this->speed.x != -speedX && !leftBlock)
        {
            this->updateBasePosX();
            this->speed.x = -speedX;
        }
        if (rightPressed && this->speed.x != speedX && !rightBlock)
        {
            this->updateBasePosX();
            this->speed.x = speedX;
        }
        if (!(rightPressed || leftPressed) && this->speed.x != 0)
        {
            this->updateBasePosX();
            this->speed.x = 0;
        }
        if (this->spacePressed && this->speed.y != -2 && !topBlock && bottomBlock)
        {
            this->updateBasePosY();
            this->speed.y = -1.7f;
            this->gravityAcceleration = GRAVITY_ACCELERATION;
        }
    }
}
