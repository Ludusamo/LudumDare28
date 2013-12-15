#ifndef WARPPORTAL_H
#define WARPPORTAL_H

#include "Entity.h"
#include "Player.h"
#include "Animation.h"

class WarpPortal : public Entity
{
    public:
        WarpPortal();
        ~WarpPortal();

        void load(sf::Vector2f pos, sf::Texture& texture, std::string& destination, std::string& tileset);
        void unload();
        void update(Player& player);
        int getState();
        std::string getDestination();
        std::string getTileset();
    protected:
    private:
        Animation animation;
        std::string destination, tileset;
        sf::FloatRect bounds;
        int state;
        enum State { NOTHING, SWITCHING };
};

#endif // WARPPORTAL_H
