#pragma once

#include <string>
#include "CheckObjectType.h"

class OperationObject
{
private:
	bool operation;
	double value;
	CheckObjectType::ObjectType typeOperation;
	
public:
	OperationObject(CheckObjectType::ObjectType, std::string);
	~OperationObject();
	double getValue();
	bool isOperation();
	CheckObjectType::ObjectType getOperationType();
	void setNewValue(double);
	void updateToAddition();
};

