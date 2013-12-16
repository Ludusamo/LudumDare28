#include "KAD.h"

KAD::KAD()
{
    //ctor
}

KAD::~KAD()
{
    //dtor
}

void KAD::load(sf::Vector2f posD, sf::Vector2f posK, sf::Texture &texture, sf::Vector2i mSize, int dir) {
    this->posK = posK;
    this->posD = posD;
    tex = texture;
    this->mSize = mSize;
    this->dir = dir;

    door.setTexture(tex);
    door.setTextureRect(sf::IntRect(dir * 32, 64, mSize.x, mSize.y));
    door.setPosition(posD.x * 32, posD.y * 32);
    key.setTexture(tex);
    key.setTextureRect(sf::IntRect(64, 32, mSize.x, mSize.y));
    key.setPosition(posK.x * 32, posK.y * 32);

    keyBound.left = key.getPosition().x;
    keyBound.top = key.getPosition().y;
    keyBound.width = mSize.x;
    keyBound.height = mSize.y;

    doorBound.left = door.getPosition().x;
    doorBound.top = door.getPosition().y;
    doorBound.width = mSize.x;
    doorBound.height = mSize.y;
}

void KAD::unload() {
    door.setTextureRect(sf::IntRect(3 * 32, 32, mSize.x, mSize.y));
    key.setTextureRect(sf::IntRect(3 * 32, 32, mSize.x, mSize.y));
    door.setPosition(32, 32);
    key.setPosition(32, 32);

    inPossesion = false;
    opened = false;
}

void KAD::update(std::vector<std::vector<int>> &colMap, Rock &rock, int dir, SoundManager& sound) {
    sf::Vector2i kTilePos((key.getPosition().x / 32), (key.getPosition().y / 32));
    if (!inPossesion) {
        if (keyBound.intersects(rock.getBounds())) {
            inPossesion = true;
            key.setTextureRect(sf::IntRect(96, 32, mSize.x, mSize.y));
            sound.playSound(3);
        }
    } else {
        key.setPosition(rock.getPosition());
    }
    if (!opened) {
        if (inPossesion) {
            switch (dir) {
            case 0:
                if ((kTilePos.y - 1 == posD.y) && (kTilePos.x == posD.x)) {
                    open(colMap);
                    sound.playSound(1);
                    opened = true;
                }
                break;
            case 1:
                if ((kTilePos.y + 1 == posD.y) && (kTilePos.x == posD.x)) {
                    open(colMap);
                    sound.playSound(1);
                    opened = true;
                }
                break;
            case 2:
                if ((kTilePos.x - 1 == posD.x) && (kTilePos.y == posD.y)) {
                    open(colMap);
                    sound.playSound(1);
                    opened = true;
                }
                break;
            case 3:
                if ((kTilePos.x + 1 == posD.x) && (kTilePos.y == posD.y)) {
                    open(colMap);
                    sound.playSound(1);
                    opened = true;
                }
                break;
            }
        }
        colMap[posD.y][posD.x] = 1;
    } else {
        colMap[posD.y][posD.x] = 0;
    }
}

void KAD::open(std::vector<std::vector<int>> &colMap) {
    door.setTextureRect(sf::IntRect((dir + 4) * 32, 64, mSize.x, mSize.y));
}
