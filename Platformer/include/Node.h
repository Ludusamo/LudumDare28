#ifndef NODE_H
#define NODE_H

#include <stdint.h>

struct Node {
    Node(uint32_t x, uint32_t y);
    uint32_t x, y;
    bool left, up, right, down;
};

#endif // NODE_H
