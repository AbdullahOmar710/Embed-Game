#include "Character.h"

Character::Character(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), health(100) {
}

int Character::getHealth() const {
    return health;
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
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

int Character::getWidth() const {
    return width;
}

int Character::getHeight() const {
    return height;
} 