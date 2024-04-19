#ifndef MAP_H
#define MAP_H

#include "Node.h"
#include "N5110.h"  // Make sure this is included
#include <vector>

class Map {
public:
    Map(int width, int height);
    void displayMap(N5110 &lcd, int centerX, int centerY);  // Modify to accept lcd reference
    int getWidth() const;
    int getHeight() const;

private:
    int width, height;
    std::vector<std::vector<Node>> grid;
};

#endif
