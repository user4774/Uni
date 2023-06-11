#include <iostream>
#include <utility>
#include "Weapons.h"
using namespace std;

Weapons::Weapons(string nam, string des, int x, int y, int wei, int pri, bool dep, int dur, int con, bool equ, int att) : Items(nam, des, x, y, wei, pri, dur), depleted(dep), condition(con), equipped(equ), attack(att) {

	depleted = dep;
	condition = con;
	equipped = equ;
	attack = att;
};
