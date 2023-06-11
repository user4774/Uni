#ifndef ITEMS_H
#define ITEMS_H
#include <iostream>
#include <utility>
using namespace std;

class Items
{
public:
	string name;
	string description;
	pair <int, int> location;
	int weight;
	int price;
	int duration;

	Items(string nam, string des, int x, int y, int wei, int pri, int dur);
};
#endif