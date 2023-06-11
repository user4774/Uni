#include <iostream>
#include "Creatures.h"
#include "GameState.h"
#include "GameInstance.h"
using namespace std;

int main() 
{
	GameInstance gameInstance;
	GameState gameState;

	gameState.LoadData("CreaturesData.xml");
	gameInstance.Run();

	return 0;
}