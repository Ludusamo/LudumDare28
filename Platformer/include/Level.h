#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <SFML/Graphics.hpp>
#include "TileData.h"
#include <Tilemap.h>
#include <Player.h>
#include "Rock.h"
#include "MapGenerator.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "InputManager.h"

#define TILE_SIZE 32
#define SCALE 2.0

class Level {
public:
    Level();
    ~Level();

    void load();
    void loadLevel(const std::string& tilesetFile, const std::string&  file);
    void saveLevel(std::string levelName);
    void generateLevel(const std::string& tilesetFile, int widthB, int heightB);
    void generateLevel(const std::string& tilesetFile, uint32_t rooms, uint32_t lining, int16_t solid_fill, int16_t nonsolid_fill);
    void loadEntities(std::vector<std::vector<std::string>> attributes, std::vector<std::vector<std::string>> contents);

    void unload();
    void update(InputManager input);
    void render(sf::RenderWindow &window);

    Player &getPlayer();
    Rock &getRock();

    std::vector<std::vector<int>> getColMap();
    int getWidth();
    int getHeight();

    // TEMPORARY
    void switchTime(bool day);
protected:
private:

    std::vector<sf::Keyboard::Key> up;
    std::vector<sf::Keyboard::Key> down;
    std::vector<sf::Keyboard::Key> left;
    std::vector<sf::Keyboard::Key> right;

    // Map
    int width, height;
    std::vector<int> tiles;

    Tilemap tmap;
    std::vector<std::vector<int> > colMap;

    void addEntity(Mob* e);
    std::vector<Mob*> entities;

    // Player
    Player player;
    sf::Texture pTex;

    // Rock
    Rock rock;
    sf::Texture rTex;

    // Shader
    sf::Shader shader;
    float ambientIntensity = .7f;
    sf::Vector3f ambientColor;
};
#endif // LEVEL_H
