#include "Player.h"

Player::Player() {
    //ctor
}

Player::~Player() {
    //dtor
}

void Player::load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize) {
    Mob::load(pos, texture, MAX_VEL, mSize);

    vertices[0].position = sf::Vector2f(0, 0);
    vertices[1].position = sf::Vector2f(mSize.x, 0);
    vertices[2].position = sf::Vector2f(mSize.x, mSize.y);
    vertices[3].position = sf::Vector2f(0, mSize.y);
    setTexCoords(0, 0);

    animation.load(0, 0, 3, .2);
}

void Player::unload() {

}

void Player::update(std::vector<std::vector<int>> colMap) {
    Mob::update(colMap);
    if (acceleration.x == 0 && acceleration.y == 0) {
        switch (currentDir) {
            case UP:
                setTexCoords(1, 0);
                break;
            case DOWN:
                setTexCoords(1, 1);
                break;
            case LEFT:
                setTexCoords(1, 2);
                break;
            case RIGHT:
                setTexCoords(1, 3);
                break;
        }
    }
}
