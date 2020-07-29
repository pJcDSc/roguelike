#include "Spider.h"
#include <iostream>
#include "Mutant.h"

using namespace std;

Spider::Spider(int hp, int ad, string name, string ctype) : Mutant(hp, ad, name, ctype) {
	//Other Spider things exclusive to Spiders
}

void Spider::moveBehavior() {
	//Other Spider things exclusive to Spiders
}

void Spider::attackBehavior() {
	//Etc.
}

Spider::~Spider() {
	//Nothing to delete here yet
}