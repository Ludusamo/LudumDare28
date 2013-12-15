#include "Charger.h"

Charger::Charger() {

}

Charger::~Charger() {

}

void Charger::load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize) {
    Enemy::load(pos, texture, MAX_VEL, mSize);
}

void Charger::unload() {
    delete this;
}

void Charger::update(std::vector<std::vector<int> > colMap) {
    Enemy::update(colMap);
}


void Charger::pursue(Entity * e, std::vector<std::vector<int16_t> > level) {
    Node first = this->pathfind(e, level)[0];
    sf::Vector2f curPos = this->getPosition();
    sf::Vector2f nxtPos = sf::Vector2f(first.x * 32, first.y * 32);
    this->setVelocityX(nxtPos.x - curPos.x > 0 ? 1 : nxtPos.x == curPos.x ? 0 : -1);
    this->setVelocityY(nxtPos.y - curPos.y > 0 ? 1 : nxtPos.y == curPos.y ? 0 : -1);
}

void Charger::attack(Entity * e) {

}

bool Charger::scan() {
    if(omniscient)
        return true;
    else {

    }
}
