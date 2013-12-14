#ifndef CHARGER_H
#define CHARGER_H

#include <SFML/Graphics.hpp>
#include <Enemy.h>


class Charger : public Enemy {
public:
    Charger();
    ~Charger();
    void load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize);
    void unload();
    void pursue();
    void attack();
    bool scan();
protected:
private:

};

#endif // CHARGER_H
