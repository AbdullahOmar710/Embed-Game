#include "Map.h"
#include "N5110.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

Map::Map(int width, int height) : width(width), height(height) {
    srand(time(NULL));  // Seed the random number generator
    grid.resize(height, std::vector<Node>(width, Node(EMPTY)));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                grid[i][j] = Node(BUSH);
            } else {
                grid[i][j] = Node((rand() % 10 < 2) ? TREE : EMPTY);
            }
        }
    }
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
            int pixel = 0;
            switch (grid[i][j].getType()) {
                case EMPTY: 
                    pixel = 0; 
                    break;
                case TREE:
                case BUSH:
                    pixel = 1; 
                    break;
            }
            lcd.setPixel(j - startCol, i - startRow, pixel);  // Simplified drawing logic
        }
    }
    lcd.drawRect(42, 24, 5, 5, FILL_BLACK);  // Character always in the center
    lcd.refresh();
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}
