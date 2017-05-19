#pragma once
#include <list>
#include "EquationObject.h"

// Using stack to label
class Stack {
private:
	std::list<Point> stack;
	int top;

public:
	Stack();
	void push(Point);
	Point pop();
	bool isEmpty();
};