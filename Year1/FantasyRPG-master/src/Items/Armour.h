#ifndef ARMOUR_H
#define ARMOUR_H
#include <iostream>
#include <utility>
#include "Items.h"
using namespace std;

class Armour : public Items
{
public:
	int condition;
	bool equipped;
	int defence;
	bool depleted;

	Armour(string, string, int, int, int, int, bool, int, int, bool, int);
};
#endif