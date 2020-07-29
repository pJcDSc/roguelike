#pragma once

#include <iostream>
#include "Mutant.h"

class Bear : public Mutant {

public:

	//Constructor
	Bear(int hp, int ad, std::string name, std::string ctype);

	//Override movebehavior
	void moveBehavior();

	//Override attackbehavior
	void attackBehavior();

	//Destructor
	~Bear();
};

