#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "Map.h"
#include "Character.h"
#include "Enemy.h"
#include "CombatSystems.h"

#include <vector>

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    void init();
    void cleanup();

    void handleEvents();
    void update();
    void render();

    void run();
    void stop();

private:
    N5110 display;
    Joystick joystick;
    Map gameMap;
   
    InterruptIn joystickButton; // Joystick button for additional interaction
    InterruptIn shootButton;
 
    Character character;        // Player's character instance
    Enemy enemy;
    
    CombatSystem combatSystem;
    
    int centerX;  // Current X coordinate of the player
    int centerY;  // Current Y coordinate of the player

    bool running; // Flag to check if the game loop should continue
    bool exiting; // Flag to check if the game should exit
};

#endif // GAME_ENGINE_H
