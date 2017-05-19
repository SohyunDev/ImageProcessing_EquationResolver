#include "Stack.h"


Stack::Stack() {
	top = 1;
}

void Stack::push(Point p) {
	stack.push_back(p);
	top++;
}

Point Stack::pop() {
	Point p;
	if (!isEmpty()) {
		top--;
		p = stack.back();
		stack.pop_back();
	}
	return p;
}

bool Stack::isEmpty() {
	if (top == 1) {
		return true;
	}
	else {
		return false;
	}
}