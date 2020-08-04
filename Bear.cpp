#include "Bear.h"
#include <iostream>
#include "Mutant.h"

using namespace std;

Bear::Bear(int hp, int ad, int x, int y) : Mutant(hp, ad, x, y) {
	//Other Bear things exclusive to Bears
}

void Bear::moveBehavior() {
	//Other Bear things exclusive to Bears
}

void Bear::attackBehavior() {
	//Etc.
}

string Bear::getType() {
	return "Bear";
}

Bear::~Bear() {
	//Nothing to delete here yet
}