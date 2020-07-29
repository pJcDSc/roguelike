#pragma once

#include <iostream>
#include "Mutant.h"

class Human : public Mutant {

public:

	//Constructor
	Human(int hp, int ad, std::string name, std::string ctype);

	//Override movebehavior
	void moveBehavior();

	//Override attackbehavior
	void attackBehavior();

	//Destructor
	~Human();
};

