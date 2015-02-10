#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include <queue>

#include "General_Include.hpp"
#include "SFML_Include.hpp"
#include "Direction.hpp"

class SnakeObject;

class Snake
{
public:
    Snake(char head, char body, char tail);
    ~Snake();

    void Initialize();
    void ChangeDir(DIRECTION dir);

    void Update(sf::Time elapsedTime);
    void CheckCollision();
    void Draw();

    void Enlarge(sf::Color color);

    bool Occupies(sf::Vector2u pos);

protected:
    std::queue<DIRECTION> dirQueue;
    DIRECTION curDir;

    char head, body, tail;

    SnakeObject* snakeHead;
    std::list<SnakeObject*> snakeBody;
    SnakeObject* snakeTail;
};

#endif