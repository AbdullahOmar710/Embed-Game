#include "CombatSystems.h"
#include <cmath>

CombatSystem::CombatSystem(Character& character, Enemy& enemy, int lockOnRadius)
    : character(character), enemy(enemy), lockOnRadius(lockOnRadius), locked(false) {

    }

void CombatSystem::update() {
    // Calculate the distance between the character and the enemy
    int dx = character.getX() - enemy.getX();
    int dy = character.getY() - enemy.getY();
    int distance = std::sqrt(dx * dx + dy * dy);

    // Check if the character is within the lock-on radius
    if (distance <= lockOnRadius) {
        // Character is within range, allow locking on
        if (!locked) {
            // TODO: Display lock-on prompt or visual indication
        }
    } else {
        // Character is out of range, unlock if previously locked
        unlock();
    }
}

bool CombatSystem::isLocked() const {
    return locked;
}

void CombatSystem::lock() {
    locked = true;

    // Calculate the bounding box that encloses both the character and the enemy
    int minX = std::min(character.getX(), enemy.getX());
    int maxX = std::max(character.getX() + character.getWidth(), enemy.getX() + enemy.getWidth());
    int minY = std::min(character.getY(), enemy.getY());
    int maxY = std::max(character.getY() + character.getHeight(), enemy.getY() + enemy.getHeight());

    // Calculate the center of the bounding box
    combatCenterX = (minX + maxX) / 2;
    combatCenterY = (minY + maxY) / 2;

    // Calculate the radius of the combat circle
    int dx = maxX - minX;
    int dy = maxY - minY;
    combatRadius = std::sqrt(dx * dx + dy * dy) / 2 + 20; // Adjust the radius as needed
}

void CombatSystem::unlock() {
    locked = false;
    combatRadius = 0;
}

int CombatSystem::getCombatCenterX() const {
    return combatCenterX;
}

int CombatSystem::getCombatCenterY() const {
    return combatCenterY;
}

int CombatSystem::getCombatRadius() const {
    return combatRadius;
} 

void CombatSystem::handleShooting() {
    if (locked) {
        int damage = 10; // Set the damage value
        enemy.takeDamage(damage);
        enemy.decreaseHealthBarWidth(0.8); // Decrease the health bar width by 1

        // Check if the enemy's health reaches zero
        if (enemy.getHealth() <= 0) {
            // For now, let's set the enemy's position outside the visible range
            enemy.setPosition(-100, -100);
        }
    }
}