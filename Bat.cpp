#include "Bat.h"
#include <iostream>
#include "Mutant.h"

using namespace std;

Bat::Bat(int hp, int ad, string name, string ctype) : Mutant(hp, ad, name, ctype) {
	//Other Bat things exclusive to Bats
}

void Bat::moveBehavior() {
	//Other Bat things exclusive to Bats
}

void Bat::attackBehavior() {
	//Etc.
}

Bat::~Bat() {
	//Nothing to delete here yet
}