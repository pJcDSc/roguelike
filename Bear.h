#pragma once

#include <iostream>
#include "Mutant.h"

class Bear : public Mutant {

public:

	//Constructor
	Bear(int hp, int ad, int x, int y);

	//Override movebehavior
	void moveBehavior();

	//Override attackbehavior
	void attackBehavior();

	//Override gettype
	std::string getType();

	//Destructor
	~Bear();
};

