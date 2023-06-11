#include <string>
#include "tinyxml2.h"
#include "GameState.h"
#include"Creatures.h"
using namespace tinyxml2;

void GameState::LoadData(const char* dataFileName)
{
	//creates an instance of XML document and loads the file into it 
	XMLDocument xmlDoc;
	xmlDoc.LoadFile(dataFileName);

	XMLElement* currentCreature = xmlDoc.FirstChildElement("GameState")->FirstChildElement("Creatures")->FirstChildElement("Creature");
	//while there are still child elemnts in the block 'Characters'
	while (currentCreature != NULL)
	{
		//saves the read data to this object
		Creatures creature;
		ReadCharacter(currentCreature, &creature);
		//adds what you read at the back of the list
		creaturesList.push_back(creature);
		//reads the next element 
		currentCreature = currentCreature->NextSiblingElement();
	}
}

void GameState::ReadCharacter(XMLElement* firstCharacter, Creatures* creature)
{
	//gets attribute of name 'Name' in the xml doc and saves it to nameAttribute
	const char* nameAttribute = firstCharacter->Attribute("Name");
	//saves this to the name attribute in the reference of the character 
	creature->name = std::string(nameAttribute);

	const char* healthPointAttribute = firstCharacter->Attribute("HealthPoints");
	creature->health = std::stoi(healthPointAttribute);

	const char* attackAttribute = firstCharacter->Attribute("Attack");
	creature->attack = std::stoi(attackAttribute);

	const char* defenceAttribute = firstCharacter->Attribute("Defence");
	creature->defence = std::stoi(defenceAttribute);
}

Creatures* GameState::GetCharacterObject(std::string objectName)
{
	std::list<Creatures>::iterator creaturesListIterator;
	//this was copied find it
	for (creaturesListIterator = creaturesList.begin(); creaturesListIterator != creaturesList.end(); creaturesListIterator++)
	{
		if (creaturesListIterator->name == objectName)
		{
			return &(*creaturesListIterator);
		}
	}
	return nullptr;
}