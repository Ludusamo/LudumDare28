#ifndef KAD_H
#define KAD_H

#include "Entity.h"
#include "Rock.h"

class KAD : public Entity
{
    public:
        KAD();
        ~KAD();

        void load(sf::Vector2f posK, sf::Vector2f posP, sf::Texture &texture, sf::Vector2i mSize, int dir);
        void unload();
        void update(std::vector<std::vector<int>> &colMap, Rock &rock, int dir);
        void open(std::vector<std::vector<int>> &colMap);
        sf::FloatRect &getBounds();
    protected:
    private:
        sf::Sprite key, door;
        sf::FloatRect keyBound, doorBound;
        sf::Vector2f posK, posD;
        sf::Vector2i mSize;
        int dir;
        bool opened = false, inPossesion = false;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            states.transform *= getTransform();
            states.texture = &tex;
            target.draw(key, states);
            target.draw(door, states);
        }
};

#endif // KAD_H
