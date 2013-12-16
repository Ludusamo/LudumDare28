#ifndef SIGN_H
#define SIGN_H

#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "string"
#include "Player.h"

class Sign : public Entity
{
    public:
        Sign();
        ~Sign();

        void load(sf::Vector2f pos, sf::Texture& texture, std::string msg);
        void unload();
        void update(Player& player);

        bool isActive();
        void setActive(bool x);
        bool active = false;

        sf::FloatRect &getBounds();
    protected:
    private:
        sf::Sprite sign, popUp;
        sf::FloatRect bounds;
        sf::Font font;
        sf::Text text;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            states.transform *= getTransform();
            states.texture = &tex;
            target.draw(sign, states);
            if (active) target.draw(popUp, states);
        }
};

#endif // SIGN_H
