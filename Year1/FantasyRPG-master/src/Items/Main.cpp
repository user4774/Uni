#include <iostream>
#include <utility>
#include "Items.cpp"
#include "Items.h"
#include "Weapons.cpp"
#include "Weapons.h"
#include "Armour.cpp"
#include "Armour.h"
#include "Keys.cpp"
#include "Keys.h"
#include "Books.cpp"
#include "Books.h"
using namespace std;

int main() {

	Items example("Void", "Void", 0, 0, 0, 0, 0); // instantiating object

	Weapons Coppersword("Copper Sword", "This is a copper sword", 0, 0, 20, 10, false, 0, 100, false, 10); //Name, Description, Location, Weight, Price, Depleted, Duration, Conditions, Equipped, Attack

	Weapons Ironsword("Iron Sword", "This is a iron sword", 0, 0, 30, 20, false, 0, 100, false, 15);

	Weapons Steelsword("Steel Sword", "This is a steel sword", 0, 0, 40, 30, false, 0, 100, false, 20);

	Weapons Blacksteelsword("Black Steel Sword", "This is a black steel sword", 0, 0, 50, 50, false, 0, 100, false, 30);

	Armour Copperarmour("Copper Armour", "This is copper armour", 0, 0, 30, 20, false, 0, 100, false, 20); //Name, Description, Location, weight, Price, depleted, Duration, Condition, Equipped, Defence

	Armour Ironarmour("Iron Armour", "This is iron armour", 0, 0, 35, 30, false, 0, 100, false, 25);

	Armour Steelarmour("Steel Armour", "This is steel armour", 0, 0, 40, 40, false, 0, 100, false, 30);

	Armour Blacksteelarmour("Black Steel Armour", "This is black steel armour", 0, 0, 50, 50, false, 0, 100, false, 50);

	Keys Bronzekey("Bronze Key", "This is a bronze key", 0, 0, 5, 30, 0, true); //Name, Description, Location, Weight, Price, Duration, Open

	Keys Silverkey("Silver Key", "This is a silver key", 0, 0, 5, 50, 0, true);

	Keys Goldkey("Gold Key", "This is a gold key", 0, 0, 5, 100, 0, true);

	Books Smallbook("Small Book", "This is a small book", 0, 0, 5, 10, 0); //Name, Description, Location, Weight, Price, Duration

	Books MediumBook("Medium Book", "This is a medium book", 0, 0, 5, 20, 0);

	Books Largebook("Large Book", "This is a large book", 0, 0, 5, 30, 0);

	return 0;
};