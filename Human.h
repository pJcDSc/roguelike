#pragma once

#include <iostream>
#include "Mutant.h"

class Human : public Mutant {

public:

	//Constructor
	Human(int hp, int ad, int x, int y);

	//Override movebehavior
	void moveBehavior();

	//Override attackbehavior
	void attackBehavior();

	//Override gettype
	std::string getType();

	//Destructor
	~Human();
};

