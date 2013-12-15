#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Entity.h"
#include <vector>


class PathFinder {
public:
    PathFinder();
    bool in_blacklist(uint32_t x, uint32_t y);
    std::vector<Node> pathfind(uint32_t srcx, uint32_t srcy, uint32_t tarx, uint32_t tary, std::vector<std::vector<int16_t> > level, int16_t can_pass=2);
    ///virtual std::vector<Node> pathfind(sf::Vector2f target, std::vector<std::vector<int16_t> > Level); Not implemented yet
    ///virtual std::vector<Node> pathfind(Entity entity, std::vector<std::vector<int16_t> > level);       Not implemented yet
protected:
private:
    static std::vector<Node> blacklist;
    std::string priority;
};

#endif // PATHFINDER_H
