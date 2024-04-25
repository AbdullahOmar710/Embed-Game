#include "Enemy.h"

Enemy::Enemy(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

void Enemy::display(N5110 &lcd) {
    lcd.drawRect(x, y, width, height, FILL_BLACK);
}

void Enemy::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int Enemy::getX() const {
    return x;
}

int Enemy::getY() const {
    return y;
}

int Enemy::getWidth() const {
    return width;
}

int Enemy::getHeight() const {
    return height;
}