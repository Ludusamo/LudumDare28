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

void Charger::pursue() {

}

void Charger::attack() {

}

bool Charger::scan() {
    if(omniscient)
        return true;
    else {

    }
}
