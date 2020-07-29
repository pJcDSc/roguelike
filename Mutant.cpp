#include <iostream>
#include "Mutant.h"
using namespace std;

/*
Default mutant class
to be overrode by children of different mob types
*/


//Substitution values:
Mutant::Mutant(int hp, int ad, string name, string ctype) {
    //Function to set up the stats of each mutant, so they can be set in int main.
    healthPoints = hp;
    attackDamage = ad;
    mutantName = name;
    chemType = ctype;
}

void Mutant::reportStatus() {
    //Function to report the stats of the mutant "objects"/characters.
    cout << mutantName << ":" << endl;
    cout << "Health: " << healthPoints << endl;
    cout << "Damage: " << attackDamage << endl;
    cout << "Chemtype: " << chemType << endl;
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

int Mutant::getAttackDamage() {
    return attackDamage;
}

int Mutant::getHealthPoints() {
    return healthPoints;
}

Mutant::~Mutant() {
    //Default destructor
}