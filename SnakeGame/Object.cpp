#include "Object.hpp"
#include "App.hpp"

void Object::Draw()
{
    sf::Sprite sprite = this->data.sprite;
    sprite.setPosition(float(this->data.position.x), float(this->data.position.y));
    sprite.setColor(this->data.color);
    App::Get()->GetWindow()->draw(sprite);
}