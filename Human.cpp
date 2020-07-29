#include "Human.h"
#include <iostream>
#include "Mutant.h"

using namespace std;

Human::Human(int hp, int ad, string name, string ctype) : Mutant(hp, ad, name, ctype) {
	//Other Human things exclusive to Humans
}

void Human::moveBehavior() {
	//Other Human things exclusive to Humans
}

void Human::attackBehavior() {
	//Etc.
}

Human::~Human() {
	//Nothing to delete here yet
}