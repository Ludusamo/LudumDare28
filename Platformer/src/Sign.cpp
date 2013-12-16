#include "Sign.h"

Sign::Sign()
{
    //ctor
}

Sign::~Sign()
{
    //dtor
}

void Sign::load(sf::Vector2f pos, sf::Texture& texture, std::string msg) {

}

void Sign::unload() {

}

void Sign::update(Player& player) {

}

bool Sign::isActive() {
    return active;
}

void Sign::setActive(bool x) {
    active = x;
}

sf::FloatRect &Sign::getBounds() {
    return bounds;
}
