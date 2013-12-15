#ifndef PPAD_H
#define PPAD_H

#include "Entity.h"
#include "Rock.h"

class PPAD : public Entity
{
    public:
        PPAD();
        ~PPAD();

        void load(sf::Vector2f posD, sf::Vector2f posP, sf::Texture &texture, sf::Vector2i mSize, int dir);
        void unload();
        void update(std::vector<std::vector<int>> &colMap, Rock &rock);
        void open(std::vector<std::vector<int>> &colMap);
        sf::FloatRect &getBounds();
    protected:
    private:
        sf::Sprite plate, door;
        sf::FloatRect plateBound, doorBound;
        sf::Vector2f posD, posP;
        sf::Vector2i mSize;
        int dir;
        bool opened = false;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            states.transform *= getTransform();
            states.texture = &tex;
            target.draw(plate, states);
            target.draw(door, states);
        }
};

#endif // PPAD_H
