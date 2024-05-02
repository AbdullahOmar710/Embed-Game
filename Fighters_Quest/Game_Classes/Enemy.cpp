#include "Enemy.h"

Enemy::Enemy(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), health(100), healthBarWidth(width + 4) {
}

int Enemy::getHealth() const {
    return health;
}

void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

float Enemy::getHealthBarWidth() const {
    return healthBarWidth;
}

void Enemy::decreaseHealthBarWidth(float amount) {
    healthBarWidth -= amount;
    if (healthBarWidth < 0) {
        healthBarWidth = 0;
    }
}

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