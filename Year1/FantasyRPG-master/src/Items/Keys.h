#ifndef KEYS_H
#define KEYS_H
#include <iostream>
#include <utility>
#include "Items.h"
using namespace std;

class Keys : public Items
{
public:
	bool open;

	Keys(string, string, int, int, int, int, int, bool);
};
#endif
