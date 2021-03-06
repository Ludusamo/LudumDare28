#ifndef ROCK_H
#define ROCK_H

#include "Mob.h"

class Rock : public Mob {
public:
    Rock();
    ~Rock();

    void load(sf::Vector2f pos, sf::Texture& texture, float MAX_VEL, sf::Vector2i mSize);
    void unload();
    void update(std::vector<std::vector<int>> colMap);

    void setBounds(sf::Vector2f bounds);
protected:
private:
    Animation movement, extend;
    enum State { FLYING, HELD, GROUND, GRABBING };
};

#endif // ROCK_H
