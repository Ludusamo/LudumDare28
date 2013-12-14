#include "Node.h"

Node::Node(uint32_t x, uint32_t y) {
    this->x = x;
    this->y = y;
    this->left  = true;
    this->up    = true;
    this->right = true;
    this->down  = true;
}

void Node::reverse() {
    this->x ^= this->y;
    this->y ^= this->x;
    this->x ^= this->y;
}
