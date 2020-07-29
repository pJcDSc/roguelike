#pragma once

#include <iostream>
#include "Mutant.h"

class Bat : public Mutant {

public:

	//Constructor
	Bat(int hp, int ad, std::string name, std::string ctype);

	//Override movebehavior
	void moveBehavior();

	//Override attackbehavior
	void attackBehavior();

	//Destructor
	~Bat();
};

