#ifndef _SNAKE_OBJECT_HPP_
#define _SNAKE_OBJECT_HPP_

#include "General_Include.hpp"
#include "SFML_Include.hpp"
#include "Object.hpp"
#include "Direction.hpp"

class SnakeObject : public Object
{
public:
    SnakeObject(
        char const * const identStr,
        sf::Sprite sprite,
        sf::Color color,
        SnakeObject* prevObj = NULL,
        SnakeObject* nextObj = NULL) : Object(identStr, sprite, color),
                                       prevObj(prevObj),
                                       nextObj(nextObj)
    {
    }

    ~SnakeObject() { }

public:
    void SetDir(DIRECTION dir) { curDir = dir; }
    void SetNextObj(SnakeObject* obj) { nextObj = obj; }
    void SetPrevObj(SnakeObject* obj) { prevObj = obj; }

    DIRECTION GetDir() { return curDir; }
    SnakeObject* GetNextObj() { return nextObj; }
    SnakeObject* GetPrevObj() { return prevObj; }
    
    void Initialize();
    void Update();
    virtual void Draw();

protected:
    DIRECTION curDir;
    SnakeObject* nextObj;
    SnakeObject* prevObj;
};

#endif