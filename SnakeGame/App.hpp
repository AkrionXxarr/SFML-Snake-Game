#ifndef _APP_HPP_
#define _APP_HPP_

#include <sstream>

#include "General_Include.hpp"
#include "SFML_Include.hpp"

const std::string fontTilePath = "TileSets/Font.png";
const std::string tilePath = "TileSets/Sprites.png";

const std::string powerUpSoundPath = "Sounds/PowerUp.ogg";
const std::string gameOverSoundPath = "Sounds/GameOver.ogg";
const std::string snakeMoveSoundPath = "Sounds/SnakeMove.ogg";

const std::string highScoreDataPath = "Data/HighScore.dat";

const std::string baseScoreMsg = "Length: ";

enum GAME_STATE { INTRO, RUNNING, GAME_OVER };

class App;
class TileSet;
class AsciiTileSet;
class Snake;
class World;
class Object;

extern App* appInstance;
class App
{
public:
    App(u32 width, u32 height, std::string appName);
    ~App();

    static App* const Get() { return appInstance; }

    sf::RenderWindow* const GetWindow() { return this->window; }
    AsciiTileSet* const GetFontSet() { return this->fontSet; }
    TileSet* const GetTileSet() { return this->tileSet; }
    std::list<Object*>* const GetObjList() { return &(this->objList); }
    World* const GetWorld() { return this->world; }
    Snake* const GetSnake() { return this->snake; }
    u32 GetScore() { return this->score; }
    sf::Sound* const GetPowerupSound() { return &(this->powerUpSound); }
    sf::Sound* const GetGameOverSound() { return &(this->gameOverSound); }
    sf::Sound* const GetSnakeMoveSound() { return &(this->snakeMoveSound); }

    void SetGameover() { this->gameState = GAME_OVER; }
    void SetScore(u32 score) 
    { 
        this->score = score; 
        std::stringstream ss;
        ss << baseScoreMsg << this->score;
        this->scoreMsg = ss.str();
    }
    void IncScore(u32 amnt) 
    { 
        this->score += amnt;
        std::stringstream ss;
        ss << baseScoreMsg << this->score;
        this->scoreMsg = ss.str();
    }


    void Run();

protected:
    sf::RenderWindow* window;
    AsciiTileSet* fontSet;
    TileSet* tileSet;
    Snake* snake;
    World* world;
    std::list<Object*> objList;

    GAME_STATE gameState;

    u32 score;
    std::string scoreMsg;

    sf::Sound powerUpSound;
    sf::Sound gameOverSound;
    sf::Sound snakeMoveSound;
};

#endif