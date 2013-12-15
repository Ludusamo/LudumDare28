#include "WarpPortal.h"

WarpPortal::WarpPortal()
{
    //ctor
}

WarpPortal::~WarpPortal()
{
    //dtor
}

void WarpPortal::load(sf::Vector2f pos, sf::Texture& texture, std::string& destination, std::string& tileset) {
    Entity::load(pos, texture);
    this->destination = destination;
    this->tileset = tileset;

    vertices[0].position = sf::Vector2f(0, 0);
    vertices[1].position = sf::Vector2f(32, 0);
    vertices[2].position = sf::Vector2f(32, 32);
    vertices[3].position = sf::Vector2f(0, 32);
    vertices[0].texCoords = sf::Vector2f(0 * 32, 3 * 32);
    vertices[1].texCoords = sf::Vector2f((0 + 1) * 32, 3 * 32);
    vertices[2].texCoords = sf::Vector2f((0 + 1) * 32, (3 + 1) * 32);
    vertices[3].texCoords = sf::Vector2f(0 * 32, (3 + 1) * 32);

    animation.load(0, 3, 8, .5);

    bounds.left = getPosition().x;
    bounds.top = getPosition().y;
    bounds.width = 32;
    bounds.height = 32;

    state = NOTHING;
}

void WarpPortal::unload() {
    setPosition(0, 0);
    state = NOTHING;
}

void WarpPortal::update(Player& player) {
    if (bounds.intersects(player.getBounds())) {
        state = SWITCHING;
        std::cout << "TELEPORT" << std::endl;
    }
    animation.update(vertices, sf::Vector2i(32, 32));
}

int WarpPortal::getState() {
    return state;
}

std::string WarpPortal::getDestination() {
    return destination;
}

std::string WarpPortal::getTileset() {
    return tileset;
}
