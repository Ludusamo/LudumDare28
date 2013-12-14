#include "Enemy.h"

std::vector<Enemy*> Enemy::enemyList;

Enemy::Enemy() {

}

Enemy::~Enemy() {

}

void Enemy::load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize) {
    Mob::load(pos, texture, MAX_VEL, mSize);

    vertices[0].position = sf::Vector2f(0, 0);
    vertices[1].position = sf::Vector2f(mSize.x, 0);
    vertices[2].position = sf::Vector2f(mSize.x, mSize.y);
    vertices[3].position = sf::Vector2f(0, mSize.y);
    vertices[0].texCoords = sf::Vector2f(0, 0);
    vertices[1].texCoords = sf::Vector2f(mSize.x, 0);
    vertices[2].texCoords = sf::Vector2f(mSize.x, mSize.y);
    vertices[3].texCoords = sf::Vector2f(0, mSize.y);

    Enemy::enemyList.push_back(this);
}

void Enemy::unload() {
    delete this;
}

//void Enemy::test() {/
//
//}

std::vector<Node> Enemy::pathfind(sf::Vector2f target, std::vector<std::vector<int16_t> > level) {
    sf::Vector2f source = this->getPosition();
    uint32_t srcx = std::floor((source.x + 1) / 32);
    uint32_t srcy = std::floor((source.y + 1) / 32);
    uint32_t tarx = std::floor((target.x + 1) / 32);
    uint32_t tary = std::floor((target.y + 1) / 32);
    for(uint32_t x = 0; x < level.size(); x++)
        for(uint32_t y = 0; y < level[0].size(); y++)
            level[x][y] = level[x][y] == 1 ? -1 : x == srcx && y == srcy ? 0 : 1;
    std::vector<Node> path;
    uint32_t x = srcx, y = srcy;
    while(true) {

    }
    return path;
}

std::vector<Node> Enemy::pathfind(Entity entity, std::vector<std::vector<int16_t> > graph) {
    return this->pathfind(entity.getPosition(), graph);
}
