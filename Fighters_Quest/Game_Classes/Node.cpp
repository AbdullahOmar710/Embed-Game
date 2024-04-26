#include "mbed.h"
#include "Node.h"

Node::Node(CellType type) : cellType(type) {}

CellType Node::getType() const {
    return cellType;
}
 