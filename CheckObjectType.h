#pragma once

#include "EquationObject.h"

class CheckObjectType // Compare class
{
public:
	enum ObjectType {
		AdditionSign = 20,
		SubstractionSign = 21,
		MultiplicationSign = 22,
		DivisionSign = 23,
		EqualSign = 24,
		Number = 25,
		Comma = 10,
		Zero = 0,
		One = 1,
		Two = 2,
		Three = 3,
		Four = 4,
		Five = 5,
		Six = 6,
		Seven = 7,
		Eight = 8,
		Nine = 9,
		Unknown = 42
	};

	CheckObjectType(bool);
	~CheckObjectType();
	ObjectType checkObject(EquationObject *); // not implement, check every object for find what is it

private:
	bool withLog;
	bool checkBottomLeft(EquationObject *);
	bool checkMiddleLeft(EquationObject *);
	bool checkTopLeft(EquationObject *);
	bool checkPropVert(EquationObject *);
	bool checkRight(EquationObject *);
	bool checkLeft(EquationObject *);
	bool checkMiddle(EquationObject *);
	bool checkCollumnLeftTop(EquationObject*);
	bool checkLine(EquationObject *, int);
	bool checkTop(EquationObject*);
	bool checkPropHor(EquationObject *);
	bool checkApproxAround(EquationObject*, int, int);
	bool checkCollumn(EquationObject*, int);

	void log(std::string);
};

