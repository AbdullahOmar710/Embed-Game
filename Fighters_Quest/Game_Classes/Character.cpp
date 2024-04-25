#include "Character.h"

Character::Character(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {
    }

void Character::display(N5110 &lcd) {
    lcd.drawRect(x, y, width, height, FILL_BLACK); // Check the fill parameter and dimensions
}

void Character::move(int dx, int dy) {
    x += dx;
    y += dy;
}

int Character::getX() const {
    return x;
}

int Character::getY() const {
    return y;
}
