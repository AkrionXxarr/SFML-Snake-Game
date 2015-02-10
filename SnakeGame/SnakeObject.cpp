#include "SnakeObject.hpp"
#include "App.hpp"
#include "AsciiTileSet.hpp"

void SnakeObject::Initialize()
{
    if (this->prevObj) 
    { 
        this->prevObj->SetNextObj(this);
    }
}

void SnakeObject::Update()
{
    sf::Vector2u tSize = App::Get()->GetTileSet()->GetTileSize();

    if (this->nextObj)
    {
        if (this->data.position == this->nextObj->GetData()->position)
        {
            return;
        }
    }

    if (this->prevObj)
    {
        prevObj->Update();
        prevObj->SetDir(this->curDir);
    }

    DIRECTION dir = this->curDir;
    if (dir == NORTH)       { this->data.position.y -= tSize.y; }
    else if (dir == EAST)   { this->data.position.x += tSize.x; }
    else if (dir == SOUTH)  { this->data.position.y += tSize.y; }
    else if (dir == WEST)   { this->data.position.x -= tSize.x; }
}

void SnakeObject::Draw()
{
    sf::Vector2u tSize = App::Get()->GetTileSet()->GetTileSize();

    if(this->prevObj) { this->prevObj->Draw(); }

    if (this->nextObj)
    {
        if (this->data.position == this->nextObj->GetData()->position)
        {
            return;
        }
    }

    this->data.sprite.setPosition(float(this->data.position.x), float(this->data.position.y));
    this->data.sprite.setColor(this->data.color);

    DIRECTION dir = this->curDir;
    if (dir == NORTH)      
    { 
        this->data.sprite.setRotation(0.0); 
    }
    else if (dir == EAST)  
    { 
        this->data.sprite.setRotation(90.0); 
        this->data.sprite.move(float(tSize.x), 0.0);
    }
    else if (dir == SOUTH) 
    { 
        this->data.sprite.setRotation(180.0); 
        this->data.sprite.move(float(tSize.x), float(tSize.y));
    }
    else if (dir == WEST)
    { 
        this->data.sprite.setRotation(-90.0); 
        this->data.sprite.move(0.0, float(tSize.y));
    }

    App::Get()->GetWindow()->draw(this->data.sprite);

    //Object::Draw();
}