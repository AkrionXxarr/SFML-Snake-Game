#include "World.hpp"
#include "App.hpp"
#include "Object.hpp"
#include "AsciiTileSet.hpp"
#include "Snake.hpp"
#include "RNG.hpp"

CRandom rng;

World::World(
        sf::Rect<u32> borderRect, 
        char borderChar, 
        char powerUp, 
        sf::Color borderColor, 
        u32 powerUpLimit) : powerUpLimit(powerUpLimit)
{
    this->borderRect = borderRect;

    this->borderObj = new Object(
                            "Border",
                            App::Get()->GetTileSet()->GetTile(3, 0),
                            borderColor
                            );

    this->powerUpObj = new Object(
                               "PowerUp",
                               App::Get()->GetTileSet()->GetTile(2, 0),
                               sf::Color(255, 255, 255)
                               );

    sf::Vector2u tSize = App::Get()->GetTileSet()->GetTileSize();

    for (u32 x = borderRect.left; x < (borderRect.width + borderRect.left); x++)
    {
        this->border.push_back(sf::Vector2u(x * tSize.x, borderRect.top * tSize.y));
        this->border.push_back(sf::Vector2u(x * tSize.x, ((borderRect.height + borderRect.top) - 1) * tSize.y));
    }

    for (u32 y = borderRect.top; y < (borderRect.height + borderRect.top); y++)
    {
        this->border.push_back(sf::Vector2u(borderRect.left * tSize.x, y * tSize.y));
        this->border.push_back(sf::Vector2u(((borderRect.width + borderRect.left) - 1) * tSize.x, y * tSize.y));
    }

    rng.Randomize();
}

World::~World()
{
    SAFE_DELETE(this->borderObj);
    SAFE_DELETE(this->powerUpObj);
}

void World::Draw()
{
    for (std::list<sf::Vector2u>::iterator itr = this->border.begin(); itr != this->border.end(); itr++)
    {
        this->borderObj->GetData()->position = *itr;
        this->borderObj->Draw();
    }

    for (std::list<PowerUpData>::iterator itr = this->powerUps.begin(); itr != this->powerUps.end(); itr++)
    {
        this->powerUpObj->GetData()->position = (*itr).position;
        this->powerUpObj->GetData()->color = (*itr).color;
        this->powerUpObj->Draw();
    }
}

void World::Update()
{
    if (rng.Random(4) % 4 == 0)
    {
        if (this->powerUps.size() < powerUpLimit)
        {
            sf::Vector2u tSize = App::Get()->GetTileSet()->GetTileSize();

            PowerUpData t;

            t.position.x = rng.Random(this->borderRect.width - 3) + 1;
            t.position.y = rng.Random(this->borderRect.height - 3) + 1;
            t.position.x *= tSize.x;
            t.position.y *= tSize.y;

            t.color.r = (124 + rng.Random(128));
            t.color.g = (124 + rng.Random(128));
            t.color.b = (124 + rng.Random(128));

            if (!App::Get()->GetSnake()->Occupies(t.position))
            {
                if (this->FindPowerUp(t.position) == this->powerUps.end())
                {
                    this->powerUps.push_back(t);
                }
            }
        }
    }
}

PowerUpData World::GrabPowerUp(sf::Vector2u pos)
{
    std::list<PowerUpData>::iterator t = FindPowerUp(pos);
    PowerUpData tData = { sf::Vector2u(0, 0), sf::Color(0, 0, 0)} ;

    if (t != this->powerUps.end())
    {
        tData = *t;
        this->powerUps.erase(t);
    }

    return tData;
}

std::list<PowerUpData>::iterator World::FindPowerUp(sf::Vector2u pos)
{
    std::list<PowerUpData>::iterator t = this->powerUps.end();

    for (std::list<PowerUpData>::iterator itr = this->powerUps.begin(); itr != this->powerUps.end(); itr++)
    {
        if (pos == (*itr).position)
        {
            t = itr;
            break;
        }
    }

    return t;
}