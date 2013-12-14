#include "Rock.h"

Rock::Rock()
{
    //ctor
}

Rock::~Rock()
{
    //dtor
}

void Rock::load(sf::Vector2f pos, sf::Texture& texture, float MAX_VEL, sf::Vector2i mSize) {
    Mob::load(pos, texture, MAX_VEL, mSize);

    vertices[0].position = sf::Vector2f(0, 0);
    vertices[1].position = sf::Vector2f(mSize.x, 0);
    vertices[2].position = sf::Vector2f(mSize.x, mSize.y);
    vertices[3].position = sf::Vector2f(0, mSize.y);
    vertices[0].texCoords = sf::Vector2f(0, 0);
    vertices[1].texCoords = sf::Vector2f(mSize.x, 0);
    vertices[2].texCoords = sf::Vector2f(mSize.x, mSize.y);
    vertices[3].texCoords = sf::Vector2f(0, mSize.y);

    movement.load(0, 0, 4, .2);
    extend.load(0, 4, 8, .2);

    currentState = FLYING;
}

void Rock::unload() {
    Mob::unload();
}

void Rock::update(std::vector<std::vector<int>> colMap) {
    moveM(colMap);

    if (currentState == FLYING) {
        animation = movement;
        if (acceleration.y < 0) {
            animation.setModifier(UP);
            animation.update(vertices, mSize);
        } else if (acceleration.y > 0) {
            animation.setModifier(DOWN);
            animation.update(vertices, mSize);
        }

        if (acceleration.x < 0) {
            animation.setModifier(LEFT);
            animation.update(vertices, mSize);
        } else if (acceleration.x > 0) {
            animation.setModifier(RIGHT);
            animation.update(vertices, mSize);
        }
        if ((acceleration.x == 0 && acceleration.y == 0) || collided)
            setState(GROUND);
    }

    if (currentState == GROUND) {
        vertices[0].texCoords = sf::Vector2f(0, 0);
        vertices[1].texCoords = sf::Vector2f(mSize.x, 0);
        vertices[2].texCoords = sf::Vector2f(mSize.x, mSize.y);
        vertices[3].texCoords = sf::Vector2f(0, mSize.y);
    }

    if (currentState == HELD) {
        vertices[0].texCoords = sf::Vector2f(0, 0);
        vertices[1].texCoords = sf::Vector2f(mSize.x, 0);
        vertices[2].texCoords = sf::Vector2f(mSize.x, mSize.y);
        vertices[3].texCoords = sf::Vector2f(0, mSize.y);
    }

    std::cout << currentState << std::endl;
    std::cout << FLYING << " " << HELD << " " << GROUND << std::endl;
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
