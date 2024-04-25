#ifndef ENEMY_H
#define ENEMY_H

#include "N5110.h"

class Enemy {
public:
    Enemy(int x, int y, int width, int height);
    void display(N5110 &lcd);
    void setPosition(int x, int y);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

private:
    int x, y;
    int width, height;
};

#endif // ENEMY_H