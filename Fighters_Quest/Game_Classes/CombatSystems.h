#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include "Character.h"
#include "Enemy.h"

class CombatSystem {
public:
    CombatSystem(Character& character, Enemy& enemy, int lockOnRadius);
    void update();
    bool isLocked() const;
    void lock();
    void unlock();

    int getCombatCenterX() const;
    int getCombatCenterY() const;
    int getCombatRadius() const;

private:
    Character& character;
    Enemy& enemy;
    int lockOnRadius;
    bool locked;

    int combatCenterX;
    int combatCenterY;
    int combatRadius;
};

#endif // COMBAT_SYSTEM_H 