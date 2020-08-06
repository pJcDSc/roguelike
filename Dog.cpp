#include "Dog.h"
#include <iostream>
#include "Mutant.h"

using namespace std;

Dog::Dog(int hp, int ad, int x, int y) : Mutant(hp, ad, x, y) {
	//Other Dog things exclusive to Dogs
}

void Dog::moveBehavior() {
	//Other Dog things exclusive to Dogs
}

void Dog::attackBehavior() {
	//Etc.
}

string Dog::getType() {
	return "Dog";
}

Dog::~Dog() {
	//Nothing to delete here yet
}
