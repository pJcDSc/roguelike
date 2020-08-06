#pragma once

#include <iostream>
#include "Mutant.h"

class Dog : public Mutant {

public:

	//Constructor
	Dog(int hp, int ad, int x, int y);

	//Override movebehavior
	void moveBehavior();

	//Override attackbehavior
	void attackBehavior();

	//Override gettype
	std::string getType();

	//Destructor
	~Dog();
};

