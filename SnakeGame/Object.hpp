#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "General_Include.hpp"
#include "SFML_Include.hpp"
#include "Direction.hpp"

unsigned long HashString(const char* identStr);

class Object;

struct ObjectData
{
    unsigned int ID;

    sf::Sprite sprite;
    sf::Color color;

    sf::Vector2u position;
};

class Object
{
public:
    Object()
    {
    }

    Object(
        char const * const identStr,
        sf::Sprite sprite,
        sf::Color color)
    {
        data.ID = HashString(identStr);
        data.sprite = sprite;
        data.color = color;
    }

    ~Object() { }

public:
    ObjectData* GetData() { return &(this->data); }

    virtual void Draw();

protected:
    ObjectData data;
};

#endif