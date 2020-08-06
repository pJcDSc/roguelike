#include "Bat.h"
#include <iostream>
#include "Mutant.h"

using namespace std;

Bat::Bat(int hp, int ad, int x, int y) : Mutant(hp, ad, x, y) {
	//Other Bat things exclusive to Bats
}

void Bat::moveBehavior() {
	//Other Bat things exclusive to Bats
}

void Bat::attackBehavior() {
	//Etc.
}

string Bat::getType() {
	return "Bat";
}

Bat::~Bat() {
	//Nothing to delete here yet
}
