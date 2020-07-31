#include <iostream>
#include "Mutant.h"
using namespace std;
using namespace sf;
/*
Default mutant class
to be overrode by children of different mob types
*/


//Substitution values:
Mutant::Mutant() {
    //Function to set up the stats of each mutant, so they can be set in int main.
    healthPoints = 1; //Default mutant. Most likely unused. Simply here for testing (?) purposes and maybe needed as a placeholder later
    attackDamage = 1;
    x = 0;
    y = 0;
    direction = rand() % 4;
    sprite = NULL;
}

Mutant::Mutant(int hp, int ad, int x, int y) {
    healthPoints = hp;
    attackDamage = ad;
    this -> x = x;
    this -> y = y;
    direction = rand() % 4;
    sprite = NULL;
}

void Mutant::setSprite(Sprite* s) {
    sprite = s;
}

Sprite* Mutant::getSprite() {
    return sprite;
}

void Mutant::reportStatus() {
    //Function to report the stats of the mutant "objects"/characters.
    cout << "Health: " << healthPoints << endl;
    cout << "Damage: " << attackDamage << endl;
}

void Mutant::move(int dx, int dy) {
    sprite -> move(dx, dy);
    x += dx;
    y += dy;
}

void Mutant::moveBehavior() {
    //Default function overriden by children
}

void Mutant::attackBehavior() {
    //Default function to be overriden by children
}

void Mutant::takeDamage(int dmg) {
    healthPoints -= dmg;
}

void Mutant::setDirection(int d) {
    direction = d;
}

int Mutant::getDirection() {
    return direction;
}

string Mutant::getType() {
    return "Mutant";
}

int Mutant::getAttackDamage() {
    return attackDamage;
}

int Mutant::getHealthPoints() {
    return healthPoints;
}

int Mutant::getX() {
    return x;
}

int Mutant::getY() {
    return y;
}

Mutant::~Mutant() {
    //Default destructor
    if (sprite != NULL) delete sprite;
}