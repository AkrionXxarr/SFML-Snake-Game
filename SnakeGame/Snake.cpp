#include "Snake.hpp"
#include "App.hpp"
#include "SnakeObject.hpp"
#include "AsciiTileSet.hpp"
#include "World.hpp"

Snake::Snake(char head, char body, char tail) : head(head), body(body), tail(tail)
{
}

Snake::~Snake()
{
    SAFE_DELETE(snakeHead);

    while (!this->snakeBody.empty())
    {
        SnakeObject* t = this->snakeBody.front();
        SAFE_DELETE(t);
        this->snakeBody.pop_front();
    }

    SAFE_DELETE(snakeTail);
}

void Snake::Initialize()
{
    sf::Vector2u tSize = App::Get()->GetTileSet()->GetTileSize();

    this->curDir = EAST;

    snakeTail = new SnakeObject(
                        "SnakeTail",
                        App::Get()->GetTileSet()->GetTile(0, 1),
                        sf::Color(255, 255, 255)
                        );

    snakeHead = new SnakeObject(
                        "SnakeHead",
                        App::Get()->GetTileSet()->GetTile(0, 0),
                        sf::Color(255, 255, 255),
                        snakeTail
                        );

    snakeHead->Initialize();
    snakeTail->Initialize();

    snakeHead->GetData()->position = sf::Vector2u(10 * tSize.x, 10 * tSize.y);
    snakeTail->GetData()->position = sf::Vector2u(10 * tSize.x, 10 * tSize.y);

    this->snakeHead->SetDir(this->curDir);
}

void Snake::ChangeDir(DIRECTION dir)
{
    DIRECTION t;

    if (this->dirQueue.empty()) { t = this->curDir; }
    else { t = this->dirQueue.back(); }

    if (this->dirQueue.size() < 3)
    {
        switch (t)
        {
        case NORTH:
            if (dir != SOUTH) { this->dirQueue.push(dir); }
            break;

        case EAST:
            if (dir != WEST) { this->dirQueue.push(dir); }
            break;

        case SOUTH:
            if (dir != NORTH) { this->dirQueue.push(dir); }
            break;

        case WEST:
            if (dir != EAST) { this->dirQueue.push(dir); }
            break;
        }
    }
}

void Snake::Update(sf::Time elapsedTime)
{
    if (!this->dirQueue.empty())
    {
        this->curDir = this->dirQueue.front();
        this->dirQueue.pop();
        this->snakeHead->SetDir(this->curDir);
    }

    CheckCollision();
    this->snakeHead->Update();
}

void Snake::CheckCollision()
{
    sf::Vector2u tSize = App::Get()->GetTileSet()->GetTileSize();
    sf::Vector2u pos = this->snakeHead->GetData()->position;
    DIRECTION dir = this->curDir;

    if (dir == NORTH)       { pos.y -= tSize.y; }
    else if (dir == EAST)   { pos.x += tSize.x; }
    else if (dir == SOUTH)  { pos.y += tSize.y; }
    else if (dir == WEST)   { pos.x -= tSize.x; }

    bool death = false;
    bool gotPowerup = false;

    // Check collision with self    
    for (std::list<SnakeObject*>::iterator itr = this->snakeBody.begin(); itr != this->snakeBody.end(); itr++)
    {
        if (pos == ((*itr)->GetData()->position))
        {
            death = true;
            break;
        }
    }

    if (pos == this->snakeTail->GetData()->position) { death = true; }

    // Check collision with world
    std::list<sf::Vector2u>* border = App::Get()->GetWorld()->GetBorder();
    std::list<PowerUpData>* powerUps = App::Get()->GetWorld()->GetPowerUps();

    for (std::list<sf::Vector2u>::iterator itr = border->begin(); itr != border->end(); itr++)
    {
        if (pos == (*itr))
        {
            death = true;
            break;
        }
    }

    // Check collision with powerup
    for (std::list<PowerUpData>::iterator itr = powerUps->begin(); itr != powerUps->end(); itr++)
    {
        if (pos == (*itr).position)
        {
            PowerUpData tData = App::Get()->GetWorld()->GrabPowerUp(pos);
            this->Enlarge(tData.color);
            App::Get()->GetPowerupSound()->play();
            App::Get()->IncScore(1);
            gotPowerup = true;
            break;
        }
    }

    // Instruct the app on gameover if death occured
    if (death) { App::Get()->SetGameover(); }
    if (!gotPowerup) { App::Get()->GetSnakeMoveSound()->play(); }
}

void Snake::Draw()
{
    this->snakeHead->Draw();
}

void Snake::Enlarge(sf::Color color)
{
    SnakeObject* t = new SnakeObject(
                                "SnakeBody",
                                App::Get()->GetTileSet()->GetTile(1, 0),
                                color
                                );

    t->SetNextObj(this->snakeHead);
    t->SetPrevObj(this->snakeHead->GetPrevObj());

    this->snakeHead->GetPrevObj()->SetNextObj(t);
    this->snakeHead->SetPrevObj(t);

    t->GetData()->position = this->snakeHead->GetData()->position;

    this->snakeBody.push_back(t);
}

bool Snake::Occupies(sf::Vector2u pos)
{
    if (pos == this->snakeHead->GetData()->position) { return true; }
    if (pos == this->snakeTail->GetData()->position) { return true; }

    for (std::list<SnakeObject*>::iterator itr = this->snakeBody.begin(); itr != this->snakeBody.end(); itr++)
    {
        if (pos == (*itr)->GetData()->position)
        {
            return true;
        }
    }

    return false;
}