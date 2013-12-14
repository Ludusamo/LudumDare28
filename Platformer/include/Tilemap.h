#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Tilemap : public sf::Drawable, public sf::Transformable {
public:
    Tilemap();
    ~Tilemap();

    bool load(const std::string& tilesetFile, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);
    bool generateLevel();
    bool unload();
protected:
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &tileset;
        target.draw(m_vertices, states);
    }
    sf::VertexArray m_vertices;
    sf::Texture tileset;
};

#endif // TILEMAP_H
