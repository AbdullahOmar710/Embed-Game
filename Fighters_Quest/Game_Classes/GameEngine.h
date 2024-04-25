#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "N5110.h"
#include "Joystick.h"
#include "Map.h"
#include "mbed.h"

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
    InterruptIn joystickButton; // Added this for joystick button

    int centerX;  // Added centerX for storing current X coordinate
    int centerY;  // Added centerY for storing current Y coordinate

    bool running;
    bool exiting;
};

#endif // GAME_ENGINE_H
