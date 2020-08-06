#pragma once

#include <iostream>
#include "Mutant.h"

class Spider : public Mutant {

public:

	//Constructor
	Spider(int hp, int ad, int x, int y);

	//Override movebehavior
	void moveBehavior();

	//Override attackbehavior
	void attackBehavior();

	//Override gettype
	std::string getType();

	//Destructor
	~Spider();
};

