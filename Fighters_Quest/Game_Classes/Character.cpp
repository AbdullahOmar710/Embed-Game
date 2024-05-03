#include "Character.h"

Character::Character(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), health(100), shooting(false) {  // Fixed line here
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
    lcd.drawSprite(x, y, 20, 19, (int *)Toria);
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

void Character::shoot() {
    shooting = true;
    shootingTimer.start();
}

bool Character::isShooting() const {
    return shooting;
}