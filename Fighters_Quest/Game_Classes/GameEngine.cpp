#include "GameEngine.h"

GameEngine::GameEngine() 
    : display(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10), // Initialize the LCD with pin numbers
      joystick(PC_3, PC_2), // Initialize the Joystick with pin numbers
      joystickButton(PC_15), // Initialize the joystick button
      gameMap(200, 200), // Initialize the game map with size directly here
      centerX(100), // Initial X coordinate in the middle of the map
      centerY(100) { // Initial Y coordinate in the middle of the map
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

    gameMap = Map(200, 200); // Larger map size for exploration
    gameMap.displayMap(display, centerX, centerY);

    // Initialize character position at the bottom of the map, centered horizontally on the path
    centerY = gameMap.getHeight() - 2; // Start near the bottom of the map
    centerX = gameMap.getPathCenterXAt(centerY); // Get the central x-coordinate of the path at the bottom

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

void GameEngine::update() {
    // Update logic can be expanded as needed
}

void GameEngine::render() {
    display.clear();
    gameMap.displayMap(display, centerX, centerY - 12); // Adjust Y to keep the path centered
    display.refresh();
}


void GameEngine::run() {
    init();
    while (running) {
        handleEvents();
        update();
        render();
        ThisThread::sleep_for(100ms); // Control refresh rate
    }
}

void GameEngine::stop() {
    running = false;
}
