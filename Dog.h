#pragma once

#include <iostream>
#include "Mutant.h"

class Dog : public Mutant {

public:

	//Constructor
	Dog(int hp, int ad, std::string name, std::string ctype);

	//Override movebehavior
	void moveBehavior();

	//Override attackbehavior
	void attackBehavior();

	//Destructor
	~Dog();
};

