#pragma once
#include <list>
#include "Creatures.h"
#include "tinyxml2.h"

class GameState
{
public:
	std::list <Creatures> creaturesList;

	void LoadData(const char* dataFileName);
	void ReadCharacter(tinyxml2::XMLElement* firstCharacter, Creatures* creature);
	Creatures* GetCharacterObject(std::string objectName);
};

