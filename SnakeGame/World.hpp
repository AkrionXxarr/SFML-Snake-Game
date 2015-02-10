#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "General_Include.hpp"
#include "SFML_Include.hpp"

class Object;

struct PowerUpData
{
    sf::Vector2u position;
    sf::Color color;
};

class World
{
public:
    World(sf::Rect<u32> borderRect, char borderChar, char powerUp, sf::Color borderColor, u32 powerUpLimit);
    ~World();

public:
    std::list<sf::Vector2u>* const GetBorder() { return &(this->border); }
    std::list<PowerUpData>* const GetPowerUps() { return &(this->powerUps); }

    void Draw();
    void Update();

    PowerUpData GrabPowerUp(sf::Vector2u pos);
    std::list<PowerUpData>::iterator FindPowerUp(sf::Vector2u pos);

protected:
    sf::Rect<u32> borderRect;

    std::list<sf::Vector2u> border;
    std::list<PowerUpData> powerUps;

    Object* borderObj;
    Object* powerUpObj;

    u32 powerUpLimit;
};

#endif