#include "Player.h"

Player::Player() {
    //ctor
}

Player::~Player() {
    //dtor
}

void Player::load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize, std::vector<bool> attributes) {
    Mob::load(pos, texture, MAX_VEL, mSize);

    this->attributes = attributes;

    vertices[0].position = sf::Vector2f(0, 0);
    vertices[1].position = sf::Vector2f(mSize.x, 0);
    vertices[2].position = sf::Vector2f(mSize.x, mSize.y);
    vertices[3].position = sf::Vector2f(0, mSize.y);
    setTexCoords(0, 0);

    animation.load(0, 0, 3, .2);

    bmX = 5;
    bmY = 1;

    bounds.top = getPosition().y + bmY;
    bounds.left = getPosition().x + bmX;
    bounds.width = 22;
    bounds.height = 30;

    flying = false;
}

void Player::unload() {

}

void Player::update(std::vector<std::vector<int>> colMap) {
    Mob::update(colMap);
    if (getCurrentState() != ATTACKING) {
        if (acceleration.x == 0 && acceleration.y == 0) {
            setCurrentState(IDLE);
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
        } else {
            setCurrentState(MOVING);
        }

        if (coolDownTimer >= COOLDOWN) {
            canAttack = true;
        } else coolDownTimer += .016;
    } else {
        if (attackTimer >= ATTACK_DURATION) {
            setCurrentState(0);
            coolDownTimer = 0;
        } else attackTimer += .016;
    }
}

void Player::throwRock(Rock& rock, int dir) {
    switch (dir) {
    case UP:
        rock.setAccelerationY(-4);
        break;
    case DOWN:
        rock.setAccelerationY(4);
        break;
    case LEFT:
        rock.setAccelerationX(-4);
        break;
    case RIGHT:
        rock.setAccelerationX(4);
        break;
    }
}

void Player::attack(Rock& rock, int dir) {
    setCurrentState(ATTACKING);
    setAccelerationX(0);
    setAccelerationY(0);
    switch (dir) {
    case UP:
        rock.setTexCoords(4, 0);
        rock.setPosition(getPosition() - sf::Vector2f(0, mSize.y));
        break;
    case DOWN:
        rock.setTexCoords(5, 0);
        rock.setPosition(getPosition() + sf::Vector2f(0, mSize.y));
        break;
    case LEFT:
        rock.setTexCoords(6, 0);
        rock.setPosition(getPosition() - sf::Vector2f(mSize.x, 0));
        break;
    case RIGHT:
        rock.setTexCoords(7, 0);
        rock.setPosition(getPosition() + sf::Vector2f(mSize.x, 0));
        break;
    }
    canAttack = false;
    attackTimer = 0;
}

void Player::teleport(Rock& rock) {
    sf::Vector2i pTilePos((getPosition().x / 32), (getPosition().y / 32));
    sf::Vector2i rTilePos((rock.getPosition().x / 32), (rock.getPosition().y / 32));

    if ((pTilePos.y - 2 == rTilePos.y) && (pTilePos.x == rTilePos.x)) {
        setPosition(rock.getPosition());
    }
    if ((pTilePos.y + 2 == rTilePos.y) && (pTilePos.x == rTilePos.x)) {
       setPosition(rock.getPosition());
    }
    if ((pTilePos.x - 2 == rTilePos.x) && (pTilePos.y == rTilePos.y)){
        setPosition(rock.getPosition());
    }
    if ((pTilePos.x + 2 == rTilePos.x) && (pTilePos.y == rTilePos.y)) {
        setPosition(rock.getPosition());
    }
}

void Player::grab() {

}

bool Player::getCanAttack() {
    return canAttack;
}

std::vector<bool> Player::getAttributes() {
    return attributes;
}

void Player::setAttributes(std::vector<bool> attributes) {
    this->attributes = attributes;
}
