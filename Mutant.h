#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
/*
Roguelike mutant parent class header
*/

class Mutant {

public:

    //Debug prints?
    void reportStatus();

    //Default movement function
    virtual void moveBehavior(); //Virtual for overriding

    //Called to move sprite and update class properties
    virtual void move(int dx, int dy);

    //Called to set the sprite
    void setSprite(sf::Sprite* s);

    //To get the sprite in case you want to change the texture or anything
    sf::Sprite* getSprite();

    //Get type of mutant (to classify between different enemies, overriden by children)
    virtual std::string getType();

    //Default attack function
    virtual void attackBehavior();

    //Check for if mutant is dead
    bool isDead();

    //Getter for health and damage
    int getHealthPoints();
    int getAttackDamage();

    //Getters for coords
    int getX();
    int getY();

    //Damage function for taking damage
    void takeDamage(int dmg);

    //Get and set direction
    void setDirection(int d);
    int getDirection();
    
    //Constructor
    Mutant();

    //Construtor v2
    Mutant(int hp, int ad, int x, int y);

    //Destructor (no idea if we will even bother with these lol)
    virtual ~Mutant();

private:
    int x; int y;
    int healthPoints;
    int attackDamage;
    int direction; //value 0-3 storing which direction it is going, can be changed later
    bool dead;
    sf::Sprite* sprite;
};
