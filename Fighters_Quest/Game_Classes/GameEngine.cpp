#include "GameEngine.h"

GameEngine::GameEngine() 
    : display(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10), // Initialize the LCD with pin numbers
      joystick(PC_3, PC_2), // Initialize the Joystick with pin numbers
      joystickButton(PC_15), // Initialize the joystick button
      
      gameMap(120, 120),  // Initialize the game map with size
      centerX(100), // Initial X coordinate in the middle of the map
      centerY(100), // Initial Y coordinate in the middle of the map
      
      character(40, 35, 7, 7), // Initialize character with position and size
      enemy(0, 0, 0, 0), // Initialize enemy with default values (Later overwritten in GameEngine::init)
      combatSystem(character, enemy, 5) // Adjust the lock-on radius as needed (How close you need to get before going into combat mode)

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
        int pathWidth = gameMap.getPathWidthAt(enemyStartY); // Get the path width at the current Y-coordinate

        // Check if there is a valid path at the current Y-coordinate
        if (pathWidth > 0) {
            int pathCenter = gameMap.getPathCenterXAt(enemyStartY);
            enemyStartX = pathCenter - enemy.getWidth() / 2; // Center the enemy horizontally on the path
            enemyPositionFound = true;
        }
    }

    enemy = Enemy(enemyStartX, enemyStartY, 5, 5);  // Create the enemy with the desired position and size

    running = true;
}

void GameEngine::cleanup() {
    // Clean up resources if any
}

void GameEngine::update() {
    combatSystem.update();
}

void GameEngine::handleEvents() {
    Direction dir = joystick.get_direction();
    if (joystickButton.read() == 0) { // Assuming joystick button is pressed when read() returns 0
        if (combatSystem.isLocked()) {
            // TODO: Initialize fighting mechanism
        } else {
            combatSystem.lock();
        }
    }

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

    // Display character
    character.display(display);
    // Display character health bar
    int characterHealthBarWidth = character.getWidth() + 2; // Increase width by 4 pixels
    int characterHealthBarHeight = 1; // Set height to 1 pixel
    int characterHealthBarX = character.getX() - 1; // Adjust X position to center the health bar
    int characterHealthBarY = character.getY() + character.getHeight() + 1;
    int characterHealthBarFill = (character.getHealth() * characterHealthBarWidth) / 100;
    display.drawRect(characterHealthBarX, characterHealthBarY, characterHealthBarWidth, characterHealthBarHeight, FILL_TRANSPARENT);
    display.drawRect(characterHealthBarX, characterHealthBarY, characterHealthBarFill, characterHealthBarHeight, FILL_BLACK);

    // Calculate the relative position of the enemy on the screen
    int enemyDisplayX = enemy.getX() - centerX + 42;
    int enemyDisplayY = enemy.getY() - centerY + 24;

    // Check if the enemy is within the visible range
    if (enemyDisplayX >= 0 && enemyDisplayX <= 84 && enemyDisplayY >= 0 && enemyDisplayY <= 48) {
        // Display the enemy on the screen
        display.drawRect(enemyDisplayX, enemyDisplayY, enemy.getWidth(), enemy.getHeight(), FILL_BLACK);
        // Display enemy health bar
        int enemyHealthBarWidth = enemy.getWidth() + 4; // Increase width by 4 pixels
        int enemyHealthBarHeight = 1; // Set height to 1 pixel
        int enemyHealthBarX = enemyDisplayX - 2; // Adjust X position to center the health bar
        int enemyHealthBarY = enemyDisplayY + enemy.getHeight() + 1;
        int enemyHealthBarFill = (enemy.getHealth() * enemyHealthBarWidth) / 100;
        display.drawRect(enemyHealthBarX, enemyHealthBarY, enemyHealthBarWidth, enemyHealthBarHeight, FILL_TRANSPARENT);
        display.drawRect(enemyHealthBarX, enemyHealthBarY, enemyHealthBarFill, enemyHealthBarHeight, FILL_BLACK);
    }
    
    // Draw the combat circle if characters are locked in combat
    if (combatSystem.isLocked()) {
        int combatCenterX = combatSystem.getCombatCenterX();
        int combatCenterY = combatSystem.getCombatCenterY();
        int combatRadius = combatSystem.getCombatRadius();

        // Calculate the relative position of the combat circle on the screen
        int combatCircleX = combatCenterX - centerX + 42;
        int combatCircleY = combatCenterY - centerY + 24;

        // Check if the combat circle is within the visible range
        if (combatCircleX >= 0 && combatCircleX <= 84 && combatCircleY >= 0 && combatCircleY <= 48) {
            // Draw the combat circle
            display.drawCircle(combatCircleX, combatCircleY, combatRadius, FILL_TRANSPARENT);
        }
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
 