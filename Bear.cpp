#include "Bear.h"
#include <iostream>
#include "Mutant.h"

using namespace std;

Bear::Bear(int hp, int ad, string name, string ctype) : Mutant(hp, ad, name, ctype) {
	//Other Bear things exclusive to Bears
}

void Bear::moveBehavior() {
	//Other Bear things exclusive to Bears
}

void Bear::attackBehavior() {
	//Etc.
}

Bear::~Bear() {
	//Nothing to delete here yet
}