#include "Level.h"
#include <cmath>

Level::Level() {

}

Level::~Level() {
    //dtor
}

void Level::load() {
    if (shader.isAvailable())
        if (!shader.loadFromFile("res/shaders/AmbientShader.glsl", sf::Shader::Fragment))
            std::cout << "Cannot load shader." << std::endl;
    shader.setParameter("texture", sf::Shader::CurrentTexture);
    ambientColor.x = 0.3f;
    ambientColor.y = 0.3f;
    ambientColor.z = 0.7f;

    shader.setParameter("ambientColor", ambientColor.x, ambientColor.y, ambientColor.z, ambientIntensity);

    pTex.loadFromFile("res/imgs/player.png");
    rTex.loadFromFile("res/imgs/rock.png");

    up.push_back(sf::Keyboard::Up);
    up.push_back(sf::Keyboard::W);
    down.push_back(sf::Keyboard::Down);
    down.push_back(sf::Keyboard::S);
    left.push_back(sf::Keyboard::Left);
    left.push_back(sf::Keyboard::A);
    right.push_back(sf::Keyboard::Right);
    right.push_back(sf::Keyboard::D);
}

void Level::loadLevel(const std::string& tilesetFile, const std::string&  file) {
    sf::Image image;
    if (!image.loadFromFile("res/lvls/" + file))
        std::cout << "Cannot Load Level." << std::endl;
    width = image.getSize().x;
    height = image.getSize().y;

    // Loading Map
    std::vector<int> bufferV;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int i = 0; i < 256; i++) {
                if (image.getPixel(x, y) == TileData::tiles[i].getLevelColor()) {
                    tiles.push_back(TileData::tiles[i].getId());
                    if (TileData::tiles[i].isSolid()) bufferV.push_back(1);
                    else if (TileData::tiles[i].isGap()) bufferV.push_back(2);
                    else bufferV.push_back(0);
                    break;
                }
            }
        }
        colMap.push_back(bufferV);
        bufferV.clear();
    }

    if (!tmap.load(tilesetFile, sf::Vector2u(32, 32), tiles, width, height))
        std::cout << "Map could not be loaded." << std::endl;
}

void Level::saveLevel(std::string levelName) {
    sf::Image image;
    image.create(width, height, sf::Color::Black);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image.setPixel(x, y, TileData::tiles[tiles[x + y * width]].getLevelColor());
        }
    }
    image.saveToFile("res/lvls/" + levelName);
}

void Level::generateLevel(const std::string& tilesetFile, int widthB, int heightB) {
    width = widthB;
    height = heightB;

    MapGenerator test("res/lvls/1.comp");
    std::vector<std::vector<int16_t> > levelBuffer = test.generate(width, height, 0.1f);

    std::vector<int> bufferV;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tiles.push_back(TileData::tiles[levelBuffer[y][x]].getId());
            if (TileData::tiles[levelBuffer[y][x]].isSolid()) bufferV.push_back(1);
            else if (TileData::tiles[levelBuffer[y][x]].isGap()) bufferV.push_back(2);
            else bufferV.push_back(0);
        }
        colMap.push_back(bufferV);
        bufferV.clear();
    }

    if (!tmap.load(tilesetFile, sf::Vector2u(32, 32), tiles, width, height))
        std::cout << "Map could not be loaded." << std::endl;
}

void Level::generateLevel(const std::string& tilesetFile, uint32_t rooms, uint32_t lining, int16_t solid_fill, int16_t nonsolid_fill) {

    MapGenerator test("res/lvls/room1.comp");
    std::vector<std::vector<int16_t> > levelBuffer = test.generate_orderly(rooms, lining, solid_fill, nonsolid_fill);
    width = levelBuffer.size();
    height = levelBuffer[0].size();

    std::vector<int> bufferV;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tiles.push_back(TileData::tiles[levelBuffer[y][x]].getId());
            if (TileData::tiles[levelBuffer[y][x]].isSolid()) bufferV.push_back(1);
            else if (TileData::tiles[levelBuffer[y][x]].isGap()) bufferV.push_back(2);
            else bufferV.push_back(0);
        }
        colMap.push_back(bufferV);
        bufferV.clear();
    }

    if (!tmap.load(tilesetFile, sf::Vector2u(32, 32), tiles, width, height))
        std::cout << "Map could not be loaded." << std::endl;
}

void Level::loadEntities(std::vector<std::vector<std::string>> attributes, std::vector<std::vector<std::string>> contents) {
    for (int i = 0; i < attributes.size(); i++) {
        switch (std::stoi(attributes[i][0])) {
            case 0:
                player.load(sf::Vector2f(std::stoi(contents[i][0]), std::stoi(contents[i][1])), pTex, 2, sf::Vector2i(32, 32));
                addEntity(&player);
                break;
            case 1:
                rock.load(sf::Vector2f(std::stoi(contents[i][0]), std::stoi(contents[i][1])), rTex, 6, sf::Vector2i(32, 32));
                addEntity(&rock);
                break;
        }
    }
}

void Level::unload() {
    tmap.unload();
    for (int e = 0; e < entities.size(); e++) {
        entities[e]->unload();
    }
}

void Level::update(InputManager input) {
    for (int e = 0; e < entities.size(); e++) {
        entities[e]->update(colMap);
    }

    if (((player.getCollision().intersects(rock.getCollision()) && rock.getCurrentState() == 2) || rock.getCurrentState() == 1) && player.getCurrentState() != 2) {
        rock.setCurrentState(1);
        rock.setTexCoords(1, 0);
    }
    if (player.getCurrentState() == 2) {
        switch (player.getDir()) {
        case 0:
            rock.setPosition(player.getPosition() - sf::Vector2f(0, 32));
            break;
        case 1:
            rock.setPosition(player.getPosition() + sf::Vector2f(0, 32));
            break;
        case 2:
            rock.setPosition(player.getPosition() - sf::Vector2f(32, 0));
            break;
        case 3:
            rock.setPosition(player.getPosition() + sf::Vector2f(32, 0));
            break;
        }
    } else if (rock.getCurrentState() == 1) {
        rock.setPosition(player.getPosition());
    }

    if (input.keyPressed(sf::Keyboard::J) && player.getCanAttack()) {
        if (rock.getCurrentState() == 1) {
            player.attack(rock, player.getDir());
        }
    }

    if (input.keyPressed(sf::Keyboard::K)) {
        if (rock.getCurrentState() == 1) {
            rock.setCurrentState(0);
            player.throwRock(rock, player.getDir());
        }
    }

    // Player movements
    if (entities[0]->getCurrentState() != 2) {
        if (input.keyPressed(up)) entities[0]->setAccelerationY(-2);
        else if (input.keyPressed(down)) entities[0]->setAccelerationY(2);
        else entities[0]->setAccelerationY(0);

        if (input.keyPressed(left)) entities[0]->setAccelerationX(-2);
        else if (input.keyPressed(right)) entities[0]->setAccelerationX(2);
        else entities[0]->setAccelerationX(0);
    }

    std::cout << entities[0]->getPosition().x << std::endl;
}

void Level::render(sf::RenderWindow &window) {
    window.draw(tmap, &shader);
    for (int e = 0; e < entities.size(); e++) {
        window.draw(*entities[e], &shader);
    }
}

void Level::addEntity(Mob* e) {
    entities.push_back(e);
}

void Level::switchTime(bool day) {

    if (day) {
        ambientIntensity = 1.0f;
        ambientColor.x = 1.0f;
        ambientColor.y = 1.0f;
        ambientColor.z = 1.0f;
        shader.setParameter("ambientColor", ambientColor.x, ambientColor.y, ambientColor.z, ambientIntensity);
    } else {
        ambientIntensity = .7f;
        ambientColor.x = .3f;
        ambientColor.y = .3f;
        ambientColor.z = .7f;
        shader.setParameter("ambientColor", ambientColor.x, ambientColor.y, ambientColor.z, ambientIntensity);
    }
}

Player &Level::getPlayer() {
    return player;
}

Rock &Level::getRock() {
    return rock;
}

std::vector<std::vector<int>> Level::getColMap() {
    return colMap;
}

int Level::getWidth() {
    return width;
}

int Level::getHeight() {
    return height;
}
