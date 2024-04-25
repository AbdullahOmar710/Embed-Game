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
    int getPathCenterXAt(int y); // Method to find the center of the path at a specific height
    // Method to check if a position is valid
    bool isValidPosition(int x, int y);
    bool isPath(int x, int y) const;


private:
    int width, height;
    std::vector<std::vector<Node>> grid;
    bool isPathBorder(int y, int x); // Helper function to check for path borders

};

#endif
