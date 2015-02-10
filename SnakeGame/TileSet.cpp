#include "TileSet.hpp"

TileSet::TileSet(std::string filePath, u32 columns, u32 rows) : filePath(filePath)
{
    bool validFile = image.loadFromFile(this->filePath);

    if (validFile)
    {
        image.createMaskFromColor(sf::Color(255, 0, 255));
        texture.loadFromImage(image);

        imageSize = image.getSize();
        tileSize = sf::Vector2u(imageSize.x / columns, imageSize.y / rows);
    }
    else
    {
        throw "TileSet: Invalid file";
    }
}

sf::Sprite TileSet::GetTile(u32 x, u32 y)
{
    sf::Vector2u relCoord = this->RelativeCoords(x, y);
    sf::Sprite tile;
    tile.setTexture(this->texture);
    tile.setTextureRect(sf::IntRect(relCoord.x, relCoord.y, this->tileSize.x, this->tileSize.y));

    return tile;
}

sf::Sprite TileSet::GetTile(sf::Vector2u coords)
{
    return GetTile(coords.x, coords.y);
}

sf::Vector2u TileSet::RelativeCoords(u32 x, u32 y)
{
    return sf::Vector2u(x * this->tileSize.x, y * this->tileSize.y);
}

sf::Vector2u TileSet::RelativeCoords(sf::Vector2u coords)
{
    return RelativeCoords(coords.x, coords.y);
}