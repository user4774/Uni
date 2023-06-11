#ifndef WEAPONS_H
#define WEAPONS_H
#include <iostream>
#include <utility>
#include "Items.h"
using namespace std;

class Weapons : public Items
{
public:
	int condition;
	bool equipped;
	int attack;
	bool depleted;

	Weapons(string, string, int, int, int, int, bool, int, int, bool, int);

};
#endif