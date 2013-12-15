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
    extend.load(0, 4, 8, .2);

    currentState = FLYING;
    flying = true;
}

void Rock::unload() {
    Mob::unload();
}

void Rock::update(std::vector<std::vector<int>> colMap) {
    moveM(colMap);

    if (currentState == FLYING) {
        animation = movement;
        if (acceleration.y < 0) {
            animation.update(vertices, mSize);
        } else if (acceleration.y > 0) {
            animation.update(vertices, mSize);
        }

        if (acceleration.x < 0) {
            animation.update(vertices, mSize);
        } else if (acceleration.x > 0) {
            animation.update(vertices, mSize);
        }
        acceleration.x *= .9;
        acceleration.y *= .9;

        if (abs(acceleration.x) <= .1 && abs(acceleration.y) <= .1) {
            acceleration.x = 0;
            acceleration.y = 0;
        }

        if ((abs(velocity.x) == 0 && abs(velocity.y) == 0))
            setState(GROUND);
    }

    if (currentState == GROUND) {
        setTexCoords(0, 0);
    }
}


void Rock::extendReach() {
    int xModifier, yModifier;
    switch (currentDir) {
    case UP:
        yModifier = -64;
        break;
    case DOWN:
        yModifier = 64;
        break;
    case LEFT:
        xModifier = -64;
        break;
    case RIGHT:
        xModifier = 64;
        break;
    }

    sf::FloatRect grabber(getPosition().x + xModifier, getPosition().y + yModifier, mSize.x, mSize.y);
}

int Rock::getState() {
    return currentState;
}

void Rock::setState(int state) {
    currentState = state;
}
