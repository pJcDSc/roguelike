#include "Spider.h"
#include <iostream>
#include "Mutant.h"

using namespace std;

Spider::Spider(int hp, int ad, int x, int y) : Mutant(hp, ad, x, y) {
	//Other Spider things exclusive to Spiders
}

void Spider::moveBehavior() {
	//Other Spider things exclusive to Spiders
}

void Spider::attackBehavior() {
	//Etc.
}

string Spider::getType() {
	return "Spider";
}

Spider::~Spider() {
	//Nothing to delete here yet
}
