#include <iostream>
#include "Creatures.h"
#include "Animals.h"
#include "Humanoids.h"
#include "Player.h"
#include "Undead.h"

bool Creatures::Attack(Creatures* defendingCreature)
{
	defendingCreature->health -= defendingCreature->defence - this->attack;
	return (defendingCreature->health <= 0);
}