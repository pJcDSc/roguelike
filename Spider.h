#pragma once

#include <iostream>
#include "Mutant.h"

class Spider : public Mutant {

public:

	//Constructor
	Spider(int hp, int ad, std::string name, std::string ctype);

	//Override movebehavior
	void moveBehavior();

	//Override attackbehavior
	void attackBehavior();

	//Destructor
	~Spider();
};

