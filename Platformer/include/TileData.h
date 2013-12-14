#ifndef TILEDATA_H
#define TILEDATA_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SFML/Graphics.hpp>

class TileData {
public:
    static TileData * tiles;
    static TileData VOID;
    static TileData STONE;
    static TileData GRASS;
    static TileData GAP;

    uint32_t getId();
    sf::Color getLevelColor();
    bool isSolid();
    bool isGap();
private:
    uint32_t id;
    sf::Color levelColor;
    bool solid, gap;

    TileData(uint32_t id, sf::Color levelColor, bool solid, bool gap);
};

#endif // TILEDATA_H
