#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "N5110.h"
#include "Joystick.h"

class MainMenu {
public:
    void init(N5110 &display);
    void handleInput(Joystick &joystick);
    void render(N5110 &display);

private:
    int selectedItem;
};

#endif // MAIN_MENU_H
