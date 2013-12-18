#include "Rock.h"

Rock::Rock() {
    //ctor
}

Rock::~Rock() {
    //dtor
}

void Rock::load(sf::Vector2f pos, sf::Texture& texture, float MAX_VEL, sf::Vector2i mSize) {
    Mob::load(pos, texture, MAX_VEL, mSize);

    vertices[0].position = sf::Vector2f(0, 0);
    vertices[1].position = sf::Vector2f(mSize.x, 0);
    vertices[2].position = sf::Vector2f(mSize.x, mSize.y);
    vertices[3].position = sf::Vector2f(0, mSize.y);
    setTexCoords(0, 0);

    movement.load(0, 1, 4, .001);
    extend.load(0, 2, 8, .2);

    currentState = GROUND;
    flying = true;
    bmX = 4;
    bmY = 4;

    bounds.width = 27;
    bounds.height = 27;
}

void Rock::unload() {
    Mob::unload();
}

void Rock::update(std::vector<std::vector<int>> colMap) {
    moveM(colMap);

    if (currentState == FLYING) {
        if (acceleration.y < 0) {
            movement.update(vertices, mSize);
        } else if (acceleration.y > 0) {
            movement.update(vertices, mSize);
        }

        if (acceleration.x < 0) {
            movement.update(vertices, mSize);
        } else if (acceleration.x > 0) {
            movement.update(vertices, mSize);
        }
        acceleration.x *= .9;
        acceleration.y *= .9;

        if (abs(acceleration.x) <= .1 && abs(acceleration.y) <= .1) {
            acceleration.x = 0;
            acceleration.y = 0;
        }

        if ((abs(velocity.x) == 0 && abs(velocity.y) == 0))
            setCurrentState(GROUND);
    }

    if (currentState == GROUND) {
        setTexCoords(0, 0);
    }

    if (currentState == GRABBING) {
        if (extend.getIndex() == 7) {
            setCurrentState(HELD);
            extend.setIndex(0);
        } else {
            extend.update(vertices, mSize);
        }
    }

    bounds.left = getPosition().x;
    bounds.top = getPosition().y;
}

void Rock::setBounds(sf::Vector2f bounds) {
    this->bounds.left = bounds.x;
    this->bounds.top = bounds.y;
}
