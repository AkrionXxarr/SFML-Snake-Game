#include "AsciiTileSet.hpp"

sf::Sprite AsciiTileSet::GetCharacter(u8 c)
{
    sf::Sprite tile;
    tile = GetTile((c % 16), (c / 16));
    return tile;
}