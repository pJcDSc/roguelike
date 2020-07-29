#pragma once
#include <iostream>
/*
Roguelike mutant parent class header
*/

class Mutant {

public:

    //Debug prints?
    void reportStatus();

    //Default movement function
    virtual void moveBehavior(); //Virtual for overriding

    //Default attack function
    virtual void attackBehavior();

    //Getter for health and damage
    int getHealthPoints();
    int getAttackDamage();

    //Damage function for taking damage
    void takeDamage(int dmg);
    
    //Constructor
    Mutant(int hp, int ad, std::string name, std::string ctype);

    //Destructor (no idea if we will even bother with these lol)
    ~Mutant();

private:
    int healthPoints;
    int attackDamage;
    std::string mutantName;
    std::string chemType;
};
