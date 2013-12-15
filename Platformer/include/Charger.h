#ifndef CHARGER_H
#define CHARGER_H

#include <SFML/Graphics.hpp>
#include <Enemy.h>
#include "Node.h"


class Charger : public Enemy {
public:
    Charger();
    ~Charger();
    void load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize);
    void unload();
    void attack(Entity * e);
    void update(std::vector<std::vector<int> > colMap);
    void pursue(Entity * e, std::vector<std::vector<int32_t> > level);
    bool scan(Entity * e);
protected:
private:

};

#endif // CHARGER_H
