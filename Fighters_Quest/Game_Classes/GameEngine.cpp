#include "GameEngine.h"

GameEngine::GameEngine() 
    : display(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10), // Initialize the LCD with pin numbers
      joystick(PC_3, PC_2), // Initialize the Joystick with pin numbers
      joystickButton(PC_15), // Initialize the joystick button
      
      gameMap(250, 250),  // Initialize the game map with size
      centerX(100), // Initial X coordinate in the middle of the map
      centerY(100), // Initial Y coordinate in the middle of the map
      
      character(40, 35, 7, 7), // Initialize character with position and size
      enemy(0, 0, 0, 0) // Initialize enemy with default values (Later overwritten in GameEngine::init)

{
    running = false;
    exiting = false;
}

GameEngine::~GameEngine() {
    cleanup();
}

void GameEngine::init() {
    display.init(LPH7366_1);
    display.setContrast(0.55);
    display.setBrightness(0.5);

    joystick.init();  // Initialize the joystick
    
    // Initialize character position at the bottom of the map, centered horizontally on the path
    centerY = gameMap.getHeight() - 2; // Start near the bottom of the map
    centerX = gameMap.getPathCenterXAt(centerY); // Get the central x-coordinate of the path at the bottom

    // Set the enemy position and size
    int enemyStartX, enemyStartY;
    bool enemyPositionFound = false;

    // Find a random position on the path for the enemy
    while (!enemyPositionFound) {
        enemyStartY = rand() % gameMap.getHeight();
        enemyStartX = gameMap.getPathCenterXAt(enemyStartY);

        // Check if the selected position is a valid path position
        if (gameMap.isPath(enemyStartX, enemyStartY)) {
            enemyPositionFound = true;
        }
    }

    enemy = Enemy(enemyStartX, enemyStartY, 5, 5);  // Create the enemy with the desired position and size

    running = true;
}

void GameEngine::cleanup() {
    // Clean up resources if any
}

void GameEngine::handleEvents() {
    Direction dir = joystick.get_direction();

    // Handle direction logic as before
    switch (dir) {
        case N:  if (centerY > 1) centerY -= 1; break;
        case S:  if (centerY < gameMap.getHeight() - 2) centerY += 1; break;
        case E:  if (centerX < gameMap.getWidth() - 2) centerX += 1; break;
        case W:  if (centerX > 1) centerX -= 1; break;
        case NE: if (centerY > 1 && centerX < gameMap.getWidth() - 2) { centerY -= 1; centerX += 1; } break;
        case SE: if (centerY < gameMap.getHeight() - 2 && centerX < gameMap.getWidth() - 2) { centerY += 1; centerX += 1; } break;
        case SW: if (centerY < gameMap.getHeight() - 2 && centerX > 1) { centerY += 1; centerX -= 1; } break;
        case NW: if (centerY > 1 && centerX > 1) { centerY -= 1; centerX -= 1; } break;
        case CENTRE: default: break; // No movement if centered or undefined
    }
}

void GameEngine::render() {
    display.clear();
    gameMap.displayMap(display, centerX, centerY);
    character.display(display);

    // Calculate the relative position of the enemy on the screen
    int enemyDisplayX = enemy.getX() - centerX + 42;
    int enemyDisplayY = enemy.getY() - centerY + 24;

    // Check if the enemy is within the visible range
    if (enemyDisplayX >= 0 && enemyDisplayX <= 84 && enemyDisplayY >= 0 && enemyDisplayY <= 48) {
        // Display the enemy on the screen
        display.drawRect(enemyDisplayX, enemyDisplayY, enemy.getWidth(), enemy.getHeight(), FILL_BLACK);
    }

    display.refresh();

}

void GameEngine::run() {
    init();
    while (running) {
        handleEvents();
        render();
        ThisThread::sleep_for(100ms); // Control refresh rate
    }
}

void GameEngine::stop() {
    running = false;
}
