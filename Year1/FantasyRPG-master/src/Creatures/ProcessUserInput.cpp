#pragma once
#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>
#include "GameState.h"
#include "Creatures.h"
#include "GameInstance.h"

//copied find source
std::vector<std::string> split(const std::string& s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		//elems.push_back(item);
		elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
	}
	return elems;
}

bool GameInstance::ProcessUserInput(std::string userInput)
{
	std::vector<std::string> inputStringParts = split(userInput, ' ');

	if (inputStringParts.size() < 1)
	{
		std::cout << "Nothing input" << std::endl;
		return true;
	}

	std::string userCommand = inputStringParts[0];
	//converts command to lower case
	std::transform(userCommand.begin(), userCommand.end(), userCommand.begin(), [](unsigned char c) { return std::tolower(c); });

	if (userCommand == "exit")
	{
		return false;
	}
	else if (userCommand == "listchara")
	{
		std::list<Creatures>::iterator creaturesIterator;
		gameState.LoadData("CreaturesData.xml");
		for (creaturesIterator = gameState.creaturesList.begin(); creaturesIterator != gameState.creaturesList.end(); ++creaturesIterator)
		{
			std::cout << "Name: " << creaturesIterator->name.c_str() << ", Health: " << creaturesIterator->health << ", Attack: " << creaturesIterator->attack << std::endl;
		}
		return true;
	}
	else if (userCommand == "attack")
	{
		gameState.LoadData("CreaturesData.xml");

		if (inputStringParts.size() != 3)
		{
			std::cout << "Invalid parameters" << std::endl;
			return true;
		}
		Creatures* attackingCreaturePtr = gameState.GetCharacterObject(inputStringParts[1]);
		if (attackingCreaturePtr == nullptr)
		{
			std::cout << "Attacking character not found" << std::endl;
			return true;
		}
		Creatures* defendingCreaturePtr = gameState.GetCharacterObject(inputStringParts[2]);
		if (defendingCreaturePtr == nullptr)
		{
			std::cout << "Defending character not found" << std::endl;
			return true;
		}
		if (attackingCreaturePtr->Attack(defendingCreaturePtr))
		{
			std::cout << "Character " << defendingCreaturePtr->name << " has been killed!" << std::endl;
			gameState.creaturesList.remove(*defendingCreaturePtr);
			return true;
		}
		return true;
	}
	else
	{
		std::cout << "Unrecognised command" << std::endl;
		return true;
	}
}