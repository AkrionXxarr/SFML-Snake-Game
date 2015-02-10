#include "Text.hpp"
#include "AsciiTileSet.hpp"
#include "App.hpp"

void text::Draw(std::string message, sf::Vector2u pos, sf::Color color)
{
    AsciiTileSet* fontSet = App::Get()->GetFontSet();
    sf::RenderWindow* window = App::Get()->GetWindow();

    std::vector<sf::Sprite> fontTable;

    for (u32 i = 0; i < message.size(); i++)
    {
        fontTable.push_back(fontSet->GetCharacter(message[i]));
    }

    for (u32 i = 0; i < fontTable.size(); i++)
    {
        fontTable[i].setPosition(float(pos.x), float(pos.y));
        fontTable[i].setColor(color);
        pos.x += fontSet->GetTileSize().x;
        window->draw(fontTable[i]);
    }
}