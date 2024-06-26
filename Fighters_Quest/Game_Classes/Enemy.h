#ifndef ENEMY_H
#define ENEMY_H

#include "N5110.h"
#include "Blazeguard.h"
#include "Shadowstrike.h"
#include "Ironclad_Titan.h"

class Enemy {
public:
    Enemy(int x, int y, int width, int height);
    void display(N5110 &lcd);
    void setPosition(int x, int y);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    int getHealth() const;
    void takeDamage(int damage);
    float getHealthBarWidth() const;
    void decreaseHealthBarWidth(float amount);

private:
    int x, y;
    int width, height;
    int health;
    float healthBarWidth;

};

#endif // ENEMY_H 