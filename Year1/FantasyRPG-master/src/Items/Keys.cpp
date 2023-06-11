#include <iostream>
#include <utility>
#include "Keys.h"
using namespace std;

Keys::Keys(string nam, string des, int x, int y, int wei, int pri, int dur, bool op) : Items(nam, des, x, y, wei, pri, dur), open(op) {

	open = op;
};
