#include "Human.h"
#include <iostream>
#include "Mutant.h"

using namespace std;

Human::Human(int hp, int ad, int x, int y) : Mutant(hp, ad, x, y) {
	//Other Human things exclusive to Humans
}

void Human::moveBehavior() {
	//Other Human things exclusive to Humans
}

void Human::attackBehavior() {
	//Etc.
}

string Human::getType() {
	return "Human";
}

Human::~Human() {
	//Nothing to delete here yet
}
