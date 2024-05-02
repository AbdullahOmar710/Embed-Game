#ifndef CHARACTER_H
#define CHARACTER_H

#include "N5110.h"

class Character {
public:
    Character(int x, int y, int width, int height);
    void display(N5110 &lcd); // Method to display the character on the LCD
    void move(int dx, int dy); // Method to move the character
    void setPosition(int x, int y); // Set character position
    int getWidth() const;
    int getHeight() const;
    
    int getHealth() const;
    void takeDamage(int damage);

    bool canLock() const;

    // Getters for position
    int getX() const;
    int getY() const;

    void shoot();
    bool isShooting() const;

    bool shooting;
    Timer shootingTimer;

private:
    int x, y; // Position of the character
    int width, height; // Width and height members

    int health;


};

#endif // CHARACTER_H