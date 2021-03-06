#pragma once

#include <iostream>
#include "Mutant.h"

class Bat : public Mutant {

public:

	//Constructor
	Bat(int hp, int ad, int x, int y);

	//Override movebehavior
	void moveBehavior();

	//Override attackbehavior
	void attackBehavior();

	//Override gettype
	std::string getType();

	//Destructor
	~Bat();
};

