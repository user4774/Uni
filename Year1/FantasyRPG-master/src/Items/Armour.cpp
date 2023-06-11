#include <iostream>
#include <utility>
#include "Armour.h"
using namespace std;

Armour::Armour(string nam, string des, int x, int y, int wei, int pri, bool dep, int dur, int con, bool equ, int def) : Items(nam, des, x, y, wei, pri, dur), depleted(dep), condition(con), equipped(equ), defence(def) {

	depleted = dep;
	condition = con;
	equipped = equ;
	defence = def;
};
