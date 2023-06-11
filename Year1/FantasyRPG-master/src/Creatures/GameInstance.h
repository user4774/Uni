#pragma once
#include "GameState.h"

class GameInstance
{
public:
	void Run();
	/// <summary>
/// The instance of the internal state of the game
/// </summary>

protected:
	std::string TakeUserInput();

	/// <param name="userInput">The user input to be processed</param>
	/// <returns>true if the game should keep running, otherwise false</returns>
	bool ProcessUserInput(std::string userInput);

	GameState gameState;

};

