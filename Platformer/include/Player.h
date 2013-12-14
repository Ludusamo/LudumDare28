#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <Mob.h>
#include "Rock.h"

class Player : public Mob {
public:
    Player();
    ~Player();

    void load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize);
    void unload();
    void update(std::vector<std::vector<int>> colMap);

protected:
private:
};

#endif // PLAYER_H
