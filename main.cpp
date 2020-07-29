//placeholder main to compile and stuff
#include <iostream>
#include "Mutant.h"
#include "Dog.h"
#include "Bear.h"
#include "Bat.h"
#include "Spider.h"
#include "Human.h"

using namespace std;

int main() {
	Dog test(1, 2, "three", "for");
	Mutant* test2 = new Dog(3, 4, "five", "six");
	delete test2;
}