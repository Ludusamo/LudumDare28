#include "Enemy.h"
#include <iostream>

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

std::vector<Node> Enemy::pathfind(uint32_t srcx, uint32_t srcy, uint32_t tarx, uint32_t tary, std::vector<std::vector<int16_t> > level) {
    for(uint32_t x = 0; x < level.size(); x++)
        for(uint32_t y = 0; y < level[0].size(); y++)
            level[x][y] = level[x][y] == 1 ? -1 : x == srcx && y == srcy ? 0 : 1;
    std::vector<Node> path;
    path.push_back(Node(srcx, srcy));
    if(srcx == tarx && srcy == tary)
        return path;
    std::string priority;
    uint32_t x = srcx, y = srcy;
    while(x != tarx || y != tary) {
        if(tarx > x && tary >= y)
            priority = "rdul";
        if(tarx == x && tary > y)
            priority = "dlru";
        if(tarx < x && tary <= y)
            priority = "ldur";
        if(tarx == x && tary < y)
            priority = "ulrd";
        for(int i = 0; i < 4; i++) {
            switch(priority[i]) {
                case 'l':
                    if(path[path.size() -1].left && x != 1 && level[x - 1][y] != -1 && (path[path.size() - 1].x != x - 1 || path[path.size() - 1].y != y)) {
                        x--;
                        path[path.size() - 1].left = false;
                        path.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'u':
                    if(path[path.size() -1].up && y != 1 && level[x][y - 1] != -1 && (path[path.size() - 1].x != x || path[path.size() - 1].y != y - 1)) {
                        path[path.size() - 1].up = false;
                        y--;
                        path.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'r':
                    if(path[path.size() -1].right && x != level.size() - 2 && level[x+1][y] != -1 && (path[path.size() - 1].x != x + 1 || path[path.size() - 1].y != y)) {
                        path[path.size() - 1].right = false;
                        x++;
                        path.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'd':
                    if(path[path.size() -1].down && y != level[0].size() - 2 && level[x][y+1] != -1 && (path[path.size() - 1].x != x || path[path.size() - 1].y != y + 1)) {
                        path[path.size() - 1].down = false;
                        y++;
                        path.push_back(Node(x,y));
                        goto BREAK;
                    }
            }
            if(i == 3) {
                path.pop_back();
                x = path[path.size() - 1].x;
                y = path[path.size() - 1].y;
            }
        }
        BREAK:
        continue;
    }
    return path;
}

std::vector<Node> Enemy::pathfind(sf::Vector2f target, std::vector<std::vector<int16_t> > level) {
    sf::Vector2f source = this->getPosition();
    uint32_t srcx = std::floor((source.x + 1) / 32);
    uint32_t srcy = std::floor((source.y + 1) / 32);
    uint32_t tarx = std::floor((target.x + 1) / 32);
    uint32_t tary = std::floor((target.y + 1) / 32);
    return this->pathfind(srcx, srcy, tarx, tary, level);
}

std::vector<Node> Enemy::pathfind(Entity entity, std::vector<std::vector<int16_t> > graph) {
    return this->pathfind(entity.getPosition(), graph);
}
