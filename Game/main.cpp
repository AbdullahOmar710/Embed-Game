#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "Map.h"
#include "Node.h"

N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_3, PC_2);

int main() {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.55);
    lcd.setBrightness(0.5);

    Map gameMap(200, 200); // Larger map size for exploration

    int centerX = 100, centerY = 100; // Start in the middle of the map
    gameMap.displayMap(lcd, centerX, centerY);

    joystick.init();  // Initialize the joystick

    while (true) {
        Direction dir = joystick.get_direction();
        // Slow down the movement by adding a smaller increment
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

        gameMap.displayMap(lcd, centerX, centerY);  // Pass the lcd object
        ThisThread::sleep_for(100ms); // Control refresh rate
    }
}