#ifndef _TILE_SET_HPP_
#define _TILE_SET_HPP_

#include <string>

#include "General_Include.hpp"
#include "SFML_Include.hpp"

class TileSet
{
public:
    TileSet(std::string filePath, u32 columns, u32 rows);
    virtual ~TileSet() { }

public:
    sf::Sprite GetTile(u32 x, u32 y);
    sf::Sprite GetTile(sf::Vector2u coords);
    sf::Vector2u GetTileSize() { return tileSize; }
    sf::Vector2u GetImageSize() { return imageSize; }
    
    sf::Vector2u RelativeCoords(u32 x, u32 y);
    sf::Vector2u RelativeCoords(sf::Vector2u coords);

protected:
    std::string filePath;

    sf::Vector2u tileSize;
    sf::Vector2u imageSize;

    sf::Image image;
    sf::Texture texture;
};

#endif