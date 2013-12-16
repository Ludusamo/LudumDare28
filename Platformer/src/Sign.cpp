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
    sign.setTexture(texture);
    sign.setTextureRect(sf::IntRect(0, 128, 32, 32));
    pos.x *= 32;
    pos.y *= 32;
    sign.setPosition(pos);

    popUpT.loadFromFile("res/imgs/sign.png");
    popUp.setTexture(popUpT);
    popUp.setPosition(100, 75);

    font.loadFromFile("res/fonts/Bellerose.ttf");
    text.setFont(font);
    text.setCharacterSize(18);
    text.setString(msg);
    text.setPosition(125, 100);

    bounds.left = sign.getPosition().x;
    bounds.top = sign.getPosition().y;
    bounds.width = 32;
    bounds.height = 32;
}

void Sign::unload() {
    sign.setTextureRect(sf::IntRect(3 * 32, 32, 32, 32));
}

void Sign::update(Player& player) {
    if (bounds.intersects(player.getBounds())) {
        active = true;
    } else {
        active = false;
    }
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

sf::Sprite &Sign::getSign() {
    return sign;
}
