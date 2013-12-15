#include "PPAD.h"

PPAD::PPAD()
{
    //ctor
}

PPAD::~PPAD()
{
    //dtor
}

void PPAD::load(sf::Vector2f posD, sf::Vector2f posP, sf::Texture &texture, sf::Vector2i mSize, int dir) {
    this->posD = posD;
    this->posP = posP;
    tex = texture;
    this->mSize = mSize;
    this->dir = dir;

    door.setTexture(tex);
    door.setTextureRect(sf::IntRect(dir * 32, 0, mSize.x, mSize.y));
    door.setPosition(posD.x * 32, posD.y * 32);
    plate.setTexture(tex);
    plate.setTextureRect(sf::IntRect(0, 32, mSize.x, mSize.y));
    plate.setPosition(posP.x * 32, posP.y * 32);

    plateBound.left = plate.getPosition().x;
    plateBound.top = plate.getPosition().y;
    plateBound.width = mSize.x;
    plateBound.height = mSize.y;

    doorBound.left = door.getPosition().x;
    doorBound.top = door.getPosition().y;
    doorBound.width = mSize.x;
    doorBound.height = mSize.y;
}

void PPAD::unload() {
    door.setPosition(-2, -2);
    plate.setPosition(-2, -2);
}

void PPAD::update(std::vector<std::vector<int>> &colMap, Rock& rock) {
    if (plateBound.intersects(rock.getBounds())) {
        plate.setTextureRect(sf::IntRect(32, 32, mSize.x, mSize.y));
        if (!opened) {
            open(colMap);
            opened = true;
        }
    } else if (!opened) {
        colMap[posD.y][posD.x] = 1;
    }
}

void PPAD::open(std::vector<std::vector<int>> &colMap) {
    std::cout << "Opened." << std::endl;
    door.setTextureRect(sf::IntRect((dir + 4) * 32, 0, mSize.x, mSize.y));
    colMap[posD.y][posD.x] = 0;
}

sf::FloatRect &PPAD::getBounds() {
    return plateBound;
}
