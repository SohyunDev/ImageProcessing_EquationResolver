#pragma once

#include <list>

#include "OperationObject.h"

class EquationOperator
{
protected:
	EquationOperator();

private:
	std::list<OperationObject*> listOperation;
	int findIndexOfNextOperator();
	double resolveOperationWithIndexOfOperator(int);
	double makeAddition(double, double);
	double makeSubstraction(double, double);
	double makeDivision(double, double);
	double makeMultiplication(double, double);
	void updateListAfterOperation(int, double);
	std::string createStringOperation();

public:
	EquationOperator(std::list<OperationObject*>);
	~EquationOperator();
	double operate();
};

