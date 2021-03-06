#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <Mob.h>
#include <cmath>
#include "Node.h"


class Enemy : public Mob {
public:
    static std::vector<Enemy*> enemyList;
    Enemy();
    ~Enemy();
    virtual void load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize);
    virtual void unload();
    void update(std::vector<std::vector<int> > colMap);
    void attack(Entity * e);
    void set_radius(uint8_t r);
    void toggle_omniscience(void);
    uint8_t get_radius(void);
    bool is_omniscient(void);
    virtual bool scan(Entity * e);
    std::vector<Node> pathfind(uint32_t srcx, uint32_t srcy, uint32_t tarx, uint32_t tary, std::vector<std::vector<int16_t> > level);
    std::vector<Node> pathfind(Entity * entity, std::vector<std::vector<int16_t> > graph);
    std::vector<Node> pathfind(sf::Vector2f target, std::vector<std::vector<int16_t> > graph);
protected:
private:
    static std::vector<Node> blacklist;
    uint8_t radius;
    bool omniscient;
    bool in_blacklist(uint32_t x, uint32_t y);
    float ATK_LBOUND, ATK_UBOUND;
    sf::Sprite p_sprite;
    sf::Texture p_tex;
};

#endif // ENEMY_H
