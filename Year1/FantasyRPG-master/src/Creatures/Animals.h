#pragma once
#include "Creatures.h"
class Animals :
    public Creatures
{
	//figure out why it hates protected 
public:
    int speed;
    int stamina;

	Animals() 
	{
		health = 100;
		attack = 10;
		defence = 5;
	}
};

