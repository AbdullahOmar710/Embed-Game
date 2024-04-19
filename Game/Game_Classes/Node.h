#ifndef NODE_H
#define NODE_H

enum CellType { EMPTY, TREE, BUSH, };

class Node {
public:
    Node(CellType type);
    CellType getType() const;

private:
    CellType cellType;
};

#endif
