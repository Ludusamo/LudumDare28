#ifndef NODE_H
#define NODE_H


struct Node {
    Node * parent;
    Node * child;
    uint32_t x, y;
};

#endif // NODE_H
