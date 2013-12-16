#include "Enemy.h"
#include <iostream>

std::vector<Enemy*> Enemy::enemyList;
std::vector<Node> Enemy::blacklist;

Enemy::Enemy() {
    this->omniscient = false;
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
    Mob::unload();
}

void Enemy::set_radius(uint8_t r) {
    this->radius = r;
}

void Enemy::toggle_omniscience(void) {
    this->omniscient ^= 1;
}

uint8_t Enemy::get_radius(void) {
    return this->radius;
}

bool Enemy::is_omniscient(void) {
    return this->omniscient;
}

void Enemy::update(std::vector<std::vector<int> > colMap) {
    Mob::update(colMap);
}

bool Enemy::scan(Entity * e) {
    for(int i = std::max((int) std::round(this->getPosition().x/32) + 5 - this->radius, 0); i < std::min((int) std::round(this->getPosition().x/32) + 5 + this-> radius, 20); i++)
        for(int j = std::max((int) std::round(this->getPosition().y/32) + 5 - this->radius, 0); j < std::min((int) std::round(this->getPosition().x/32) + 5 + this->radius, 20); j++)
            if(std::round(e->getPosition().x/32) == i && std::round(e->getPosition().y/32) == j)
                return true;
    return false;
}

//void Enemy::test() {/
//
//}

bool Enemy::in_blacklist(uint32_t x, uint32_t y) {
    for(int i = 0; i < Enemy::blacklist.size(); i++)
        if(x == Enemy::blacklist[i].x && y == Enemy::blacklist[i].y)
            return true;
    return false;
}

std::vector<Node> Enemy::pathfind(uint32_t srcy, uint32_t srcx, uint32_t tary, uint32_t tarx, std::vector<std::vector<int16_t> > level) {
    for(uint32_t x = 0; x < level.size(); x++)
        for(uint32_t y = 0; y < level[0].size(); y++)
            level[x][y] = level[x][y] == 1 || level[x][y] == 2 ? -1 : x == srcx && y == srcy ? 0 : 1;
    std::vector<Node> path;
    path.push_back(Node(srcx, srcy));
    if(srcx == tarx && srcy == tary)
        return path;
    std::string priority;
    uint32_t x = srcx, y = srcy;
    while(x != tarx || y != tary) {
        if(tarx > x && tary > y)
            priority = "rdul";
        else if(tarx == x && tary > y)
            priority = "dlru";
        else if (tarx > x && tary == y)
            priority = "dlru";
        else if(tarx < x && tary < y)
            priority = "ludr";
        else if(tarx == x && tary < y)
            priority = "ulrd";
        else if(tarx < x && tary == y)
            priority = "ludr";
        else if(tarx < x && tary > y)
            priority = "ldur";
        else if(tarx > x && tary < y)
            priority = "rdul";
        for(int i = 0; i < 4; i++) {
            switch(priority[i]) {
                case 'l':
                    if(path[path.size() -1].left && x != 1 && level[x - 1][y] == 1 && !in_blacklist(x-1,y)) {
                        x--;
                        path[path.size() - 1].left = false;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'u':
                    if(path[path.size() -1].up && y != 1 && level[x][y - 1] == 1 && !in_blacklist(x,y-1)) {
                        path[path.size() - 1].up = false;
                        y--;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'r':
                    if(path[path.size() -1].right && x != level.size() - 2 && level[x+1][y] == 1 && !in_blacklist(x+1,y)) {
                        path[path.size() - 1].right = false;
                        x++;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'd':
                    if(path[path.size() -1].down && y != level[0].size() - 2 && level[x][y+1] == 1 && !in_blacklist(x,y+1)) {
                        path[path.size() - 1].down = false;
                        y++;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
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
    blacklist.clear();
    for(int i = 0; i < path.size(); i++)
        path[i].reverse();
    return path;
}

std::vector<Node> Enemy::pathfind(sf::Vector2f target, std::vector<std::vector<int16_t> > level) {
    sf::Vector2f source = this->getPosition();
    uint32_t srcx = std::round(source.x / 32) + 5;
    uint32_t srcy = std::round(source.y / 32) + 5;
    uint32_t tarx = std::round(target.x / 32);
    uint32_t tary = std::round(target.y / 32);
    //std::cout << srcx << " " << srcy << " " << tarx << " " << tary << std::endl;
    return this->pathfind(srcx, srcy, tarx, tary, level);
}

std::vector<Node> Enemy::pathfind(Entity * entity, std::vector<std::vector<int16_t> > graph) {
    return this->pathfind(entity->getPosition(), graph);
}
