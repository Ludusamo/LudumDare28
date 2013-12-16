#include "Charger.h"

Charger::Charger() {
    this->toggle_omniscience();
    this->set_radius(3);
}

Charger::~Charger() {

}

void Charger::load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize) {
    Enemy::load(pos, texture, MAX_VEL, mSize);
}

void Charger::unload() {
    Enemy::unload();
}

void Charger::update(std::vector<std::vector<int> > colMap) {
    Enemy::update(colMap);
}


void Charger::pursue(Entity * e, std::vector<std::vector<int32_t> > level) {
    if(this->scan(e)) {
        std::vector<std::vector<int16_t> > buffer(level.size(), std::vector<int16_t>(level[0].size()));
        for(int i = 0; i < buffer.size(); i++)
            for(int j = 0; j < buffer[0].size(); j++)
                buffer[i][j] = level[i][j];
        Node first = this->pathfind(e, buffer)[1];
        first = std::round(this->getPosition().x/32) + 5 == std::round(e->getPosition().x/32) && std::round(this->getPosition().y/32) + 5 == std::round(e->getPosition().y/32) ? Node(std::round(this->getPosition().x/32) + 5, std::round(this->getPosition().y/32) + 5) : first;
        std::cout << std::round(e->getPosition().x/32) << " " << std::round(e->getPosition().y/32) << "\t" << first.x << " " << first.y << std::endl;
    }
}

void Charger::attack(Entity * e) {

}

bool Charger::scan(Entity * e) {
    if(this->is_omniscient())
        return true;
    else {
        return Enemy::scan(e);
    }
}
