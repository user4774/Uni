#ifndef BOOKS_H
#define BOOKS_H
#include <iostream>
#include <utility>
#include "Items.h"
using namespace std;

class Books : public Items
{
public:
	Books(string, string, int, int, int, int, int);
};
#endif