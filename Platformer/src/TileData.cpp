#include "TileData.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

TileData * TileData::tiles = (TileData*) malloc(sizeof(TileData) * 256);
TileData TileData::VOID(0, sf::Color(0, 0, 0), true, false);
TileData TileData::STONE(1, sf::Color(68, 68, 68), true, false);
TileData TileData::GRASS(2, sf::Color(0, 255, 0), false, false);
TileData TileData::GAP(3, sf::Color(255, 255, 255), false, true);

TileData::TileData(uint32_t id, sf::Color levelColor, bool solid, bool gap) {
	this->id = id;
	this->levelColor = levelColor;
	this->solid = solid;
	this->gap = gap;
	tiles[id] = *this;
}

uint32_t TileData::getId() {
	return id;
}

sf::Color TileData::getLevelColor() {
	return levelColor;
}

bool TileData::isSolid() {
	return solid;
}

bool TileData::isGap() {
    return gap;
}
