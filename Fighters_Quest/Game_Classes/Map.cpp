#include "Map.h"
#include "N5110.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

Map::Map(int width, int height) : width(width), height(height) {
    srand(time(NULL));  // Seed the random number generator
    grid.resize(height, std::vector<Node>(width, Node(EMPTY)));

    // Randomly place trees and bushes, excluding the border
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            grid[i][j] = (rand() % 10 < 2) ? Node(TREE) : Node(EMPTY);
        }
    }
    
    // Define the edges as bushes
    for (int i = 0; i < height; i++) {
        grid[i][0] = Node(BUSH);
        grid[i][width - 1] = Node(BUSH);
    }
    for (int j = 0; j < width; j++) {
        grid[0][j] = Node(BUSH);
        grid[height - 1][j] = Node(BUSH);
    }

    // Create a winding path by clearing a line through the trees and bushes
    int path_x = width / 2; // Start in the middle of the width
    for (int y = 0; y < height; y++) {
        int pathWidth = 27; // The path will be 27 tiles wide
        for (int x_offset = -pathWidth / 2; x_offset <= pathWidth / 2; x_offset++) {
            grid[y][std::max(0, std::min(width - 1, path_x + x_offset))] = Node(PATH);
        }

        // Place rocks in a more spaced manner along the sides of the path
        for (int x_offset = -pathWidth / 2 - 2; x_offset <= pathWidth / 2 + 2; x_offset++) {
            if (abs(x_offset) == pathWidth / 2 + 1) { // Only place rocks directly adjacent to the path
                if (y % 2 == 0) {  // Place a rock every 2 rows for a less dense path
                    int rockX = std::max(0, std::min(width - 1, path_x + x_offset));
                    grid[y][rockX] = Node(ROCK);
                }
            }
        }

        // Randomly change path direction
        if (rand() % 10 < 3) {  // 30% chance to change direction
            path_x += rand() % 3 - 1; // Shift path left or right slightly
            path_x = std::max(pathWidth / 2, std::min(path_x, width - pathWidth / 2)); // Keep path within bounds
        }
    }
}

// Helper function to determine if a tile is the border of the path
bool Map::isPathBorder(int y, int x) {
    // Check if the adjacent tiles are PATH and current is not, then it's a border
    bool adjacentPath = false;
    if (x > 0) adjacentPath |= (grid[y][x-1].getType() == PATH);
    if (x < width - 1) adjacentPath |= (grid[y][x+1].getType() == PATH);
    if (y > 0) adjacentPath |= (grid[y-1][x].getType() == PATH);
    if (y < height - 1) adjacentPath |= (grid[y+1][x].getType() == PATH);

    return grid[y][x].getType() != PATH && adjacentPath;
}

bool Map::isPath(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return grid[y][x].getType() == PATH;
    }
    return false;
}

void Map::displayMap(N5110 &lcd, int centerX, int centerY) {
    int halfHeight = 24;
    int halfWidth = 42;
    int startRow = std::max(0, centerY - halfHeight);
    int endRow = std::min(height, centerY + halfHeight);
    int startCol = std::max(0, centerX - halfWidth);
    int endCol = std::min(width, centerX + halfWidth);

    lcd.clear();
    for (int i = startRow; i < endRow; i++) {
        for (int j = startCol; j < endCol; j++) {
            switch (grid[i][j].getType()) {
                case EMPTY:
                    // No pixel set for empty spaces
                    break;
                case TREE:
                case BUSH:
                    lcd.setPixel(j - startCol, i - startRow, 1);
                    break;
                case PATH:
                    lcd.setPixel(j - startCol, i - startRow, 0); // Path with clear pixel
                    break;
                case ROCK:
                    // Draw each rock as a larger cluster of pixels
                    lcd.setPixel(j - startCol, i - startRow, 1); // Center pixel
                    if (j - startCol > 0) lcd.setPixel(j - startCol - 1, i - startRow, 1); // Left pixel
                    if (j - startCol < halfWidth * 2 - 1) lcd.setPixel(j - startCol + 1, i - startRow, 1); // Right pixel
                    if (i - startRow > 0) lcd.setPixel(j - startCol, i - startRow - 1, 1); // Top pixel
                    if (i - startRow < halfHeight * 2 - 1) lcd.setPixel(j - startCol, i - startRow + 1, 1); // Bottom pixel
                    break;
            }
        }
    }

    lcd.refresh(); // Refresh the display once all drawing is done
}

int Map::getPathWidthAt(int y) const {
    int pathWidth = 0;
    for (int x = 0; x < width; x++) {
        if (grid[y][x].getType() == PATH) {
            pathWidth++;
        }
    }
    return pathWidth;
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

int Map::getPathCenterXAt(int y) {
    int start_x = -1, end_x = -1;
    for (int x = 0; x < width; x++) {
        if (grid[y][x].getType() == PATH) {
            if (start_x == -1) start_x = x; // first path tile found
            end_x = x; // continues to assign until the last path tile
        }
    }
    if (start_x != -1 && end_x != -1) {
        return (start_x + end_x) / 2; // return the middle of the path segment
    }
    return width / 2; // fallback to the middle of the map if no path is found
}

