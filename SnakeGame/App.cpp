#include <fstream>
#include <sstream>

#include "App.hpp"
#include "AsciiTileSet.hpp"
#include "Direction.hpp"
#include "Snake.hpp"
#include "World.hpp"
#include "Text.hpp"

App* appInstance = NULL;

App::App(u32 width, u32 height, std::string appName)
{
    if (!appInstance) { appInstance = this; }

    try { this->fontSet = new AsciiTileSet(fontTilePath); }
    catch (char* msg) { std::cout << msg << std::endl; }

    try { this->tileSet = new TileSet(tilePath, 4, 4); }
    catch (char* msg) { std::cout << msg << std::endl; }


    sf::Vector2u tSize = this->tileSet->GetTileSize();
    sf::Vector2u fSize = this->fontSet->GetTileSize();
    // Add fSize to height for score message
    this->window = new sf::RenderWindow(sf::VideoMode(width * tSize.x, ((height) * tSize.y) + fSize.y), appName);

    this->snake = new Snake('@', '#', 'o');
    this->snake->Initialize();

    this->world = new World(sf::Rect<u32>(0, 0, width, height), char(178), 'x', sf::Color(60, 80, 128), 200);

    this->SetScore(2);
}

App::~App()
{
    SAFE_DELETE(this->window);
    SAFE_DELETE(this->snake);
    SAFE_DELETE(this->world);
}

void App::Run()
{
    bool paused = false;
    bool newHighScore = false;

    u32 highScore = 0;

    std::stringstream ss;
    std::ifstream file(highScoreDataPath, std::ios::binary);
    if (!file.is_open())
    {
        std::ofstream tempFile(highScoreDataPath, std::ios::binary | std::ios::trunc);
        tempFile.close();
    }
    else
    {
        file.read(reinterpret_cast<char*>(&highScore), sizeof(u32));
    }
    file.close();

    sf::Vector2u winSize = this->window->getSize();
    sf::Vector2u tSize = this->tileSet->GetTileSize();
    sf::Vector2u fSize = this->fontSet->GetTileSize();

    sf::Event event;
    sf::Clock clock;

    sf::SoundBuffer powerUpBuffer;
    sf::SoundBuffer gameOverbuffer;
    sf::SoundBuffer snakeMoveBuffer;

    powerUpBuffer.loadFromFile(powerUpSoundPath);
    this->powerUpSound.setBuffer(powerUpBuffer);
    gameOverbuffer.loadFromFile(gameOverSoundPath);
    this->gameOverSound.setBuffer(gameOverbuffer);
    snakeMoveBuffer.loadFromFile(snakeMoveSoundPath);
    this->snakeMoveSound.setBuffer(snakeMoveBuffer);

    this->gameState = INTRO;

    while (this->window->isOpen())
    {
        switch (this->gameState)
        {
        case INTRO:
            while (this->window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    this->window->close();
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    this->gameState = RUNNING;
                }
            }

            this->window->clear();
            text::Draw(
                "Directons: Use the arrow keys for control & space to pause.", 
                sf::Vector2u(2 * fSize.x, ((winSize.y / 2) - 1 * fSize.y) - 4 * tSize.y), 
                sf::Color(255, 255, 255)
                );
            text::Draw(
                "Press any key to continue.", 
                sf::Vector2u((winSize.x / 2) - 15 * fSize.x, ((winSize.y / 2) + 1 * fSize.y) - 4 * tSize.y), 
                sf::Color(255, 255, 255)
                );
            this->window->display();
            break;
            break;

        case RUNNING:
            while (this->window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    this->window->close();
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)    { this->snake->ChangeDir(NORTH); }
                    if (event.key.code == sf::Keyboard::Right) { this->snake->ChangeDir(EAST); }
                    if (event.key.code == sf::Keyboard::Down)  { this->snake->ChangeDir(SOUTH); }
                    if (event.key.code == sf::Keyboard::Left)  { this->snake->ChangeDir(WEST); }

                    if (event.key.code == sf::Keyboard::Space) { paused = !paused; }
                }
            }

            if (!paused)
            {
                if (clock.getElapsedTime().asSeconds() > .25)
                {
                    this->snake->Update(clock.getElapsedTime());
                    this->world->Update();
                    clock.restart();
                }

                if (this->gameState == GAME_OVER) 
                { 
                    this->gameOverSound.play();
                    if (this->score > highScore)
                    {
                        highScore = this->score;
                    }
                    ss << "Longest Snake: " << highScore;

                    std::ofstream tempFile(highScoreDataPath, (std::ios::out | std::ios::binary | std::ios::trunc));
                    tempFile.write(reinterpret_cast<char*>(&highScore), sizeof(u32));
                    tempFile.close();

                    break; 
                }

                this->window->clear();
                this->snake->Draw();
                this->world->Draw();
                text::Draw(this->scoreMsg, sf::Vector2u(1 * tSize.x, winSize.y - fSize.y), sf::Color(255, 255, 255));
                this->window->display();
            }
            break;

        case GAME_OVER:
            while (this->window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    this->window->close();
                }
            }

            this->window->clear();
            text::Draw("Game Over", sf::Vector2u((winSize.x / 2) - 5 * fSize.x, ((winSize.y / 2) - 1 * fSize.y) - 4 * tSize.y), sf::Color(255, 255, 255));
            text::Draw(this->scoreMsg, sf::Vector2u((winSize.x / 2) - 5 * fSize.x, ((winSize.y / 2) + 1 * fSize.y) - 4 * tSize.y), sf::Color(255, 255, 255));
            text::Draw(ss.str(), sf::Vector2u((winSize.x / 2) - 5 * fSize.x, ((winSize.y / 2) + 3 * fSize.y) - 4 * tSize.y), sf::Color(255, 255, 255));
            this->window->display();
            break;
        }
    }
}