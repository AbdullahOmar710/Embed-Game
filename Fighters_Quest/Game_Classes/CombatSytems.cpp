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

    // Set the center of the combat circle to the enemy's position
    combatCenterX = enemy.getX() + enemy.getWidth() / 2;
    combatCenterY = enemy.getY() + enemy.getHeight() / 2;

    // Calculate the distance from the character to the center of the enemy
    int dx = (character.getX() + character.getWidth() / 2) - combatCenterX;
    int dy = (character.getY() + character.getHeight() / 2) - combatCenterY;

    // Calculate the radius of the combat circle
    combatRadius = std::sqrt(dx * dx + dy * dy) + 15; // Adjust the radius as needed by changing the number at the end 

    // Optionally adjust the radius to align exactly at the edge of the enemy
    combatRadius -= std::min(enemy.getWidth(), enemy.getHeight()) / 2;
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
        enemy.decreaseHealthBarWidth(2); // Decrease the health bar width by 1

        // Check if the enemy's health reaches zero
        if (enemy.getHealth() <= 0) {
            // For now, let's set the enemy's position outside the visible range
            enemy.setPosition(-100, -100);
        }
    }
}