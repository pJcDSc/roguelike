#include "Dog.h"
#include <iostream>
#include "Mutant.h"

using namespace std;

Dog::Dog(int hp, int ad, string name, string ctype) : Mutant(hp, ad, name, ctype) {
	//Other dog things exclusive to dogs
}

void Dog::moveBehavior() {
	//Other dog things exclusive to dogs
}

void Dog::attackBehavior() {
	//Etc.
}

Dog::~Dog() {
	//Nothing to delete here yet
}