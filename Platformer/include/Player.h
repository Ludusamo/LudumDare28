#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <Mob.h>
#include "Rock.h"

#define ATTACK_DURATION .5
#define COOLDOWN 1

class Player : public Mob {
public:
    Player();
    ~Player();

    void load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize);
    void unload();
    void update(std::vector<std::vector<int>> colMap);
    void throwRock(Rock& rock, int dir);
    void attack(Rock& rock, int dir);

    int getCurrentState();
    void setCurrentState(int state);
    int currentState;

    bool getCanAttack();
    bool canAttack = true;
protected:
private:

    float attackTimer, coolDownTimer;

    enum State { IDLE, MOVING, ATTACKING };
};

#endif // PLAYER_H
