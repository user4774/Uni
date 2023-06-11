#pragma once
#include <iostream>
#include <string>
#include<utility>

class Creatures
{
//when inventoryName is created, add here
public:
	//std::pair<int, int> location;

	std::string name;
	//make this protected and a method that outputs it 
	//std::string description;
	int health;
	int attack;
	int defence; 
	//int consitution; 
	//int level;
	//const int maxHealth;

	//currently set to void, change later 
	void Flee(int constitution);
	std::string ReadDescription(std::string descprition);

	bool Attack(Creatures* defendingCreature);

	//copied find source 
	bool operator == (const Creatures& creature) const { return name == creature.name && attack == creature.attack && health == creature.health; }
	bool operator != (const Creatures& creature) const { return !operator==(creature); }

};