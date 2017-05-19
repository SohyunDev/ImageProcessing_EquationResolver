#pragma once

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"

#include "EquationPicture.h"
#include "EquationPictureCutter.h"
#include "CheckObjectType.h"
#include "OperationObject.h"
#include "EquationOperator.h"

class Resolver // Main class, resolver
{
public:
	Resolver(bool = false); // not important
	~Resolver();
	std::string newEquation(EquationPicture *); // first call

private:

	EquationPictureCutter* cutter;
	CheckObjectType *compare;
	bool withLog;

	double resolve();
	//std::string createStringOperation(std::list<OperationObject*>);
	void log(std::string);
};