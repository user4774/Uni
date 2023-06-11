#include<iostream>
#include <string>
#include "GameInstance.h"

void GameInstance::Run()
{
	bool shouldContinue;
	//is a do while as it should run at least once. If false it terminates
	do
	{
		std::string userInput = TakeUserInput();
		shouldContinue = ProcessUserInput(userInput);
	} while (shouldContinue);
}

std::string GameInstance::TakeUserInput()
{
	std::string userInput;
	std::getline(std::cin, userInput);

	return userInput;
}
