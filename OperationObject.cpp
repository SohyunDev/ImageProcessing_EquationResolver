#include "OperationObject.h"

OperationObject::OperationObject(CheckObjectType::ObjectType object, std::string value = "")
{
	if (object >= 20 && object != CheckObjectType::Unknown && object != CheckObjectType::Number) {
		this->operation = true;
		this->value = -1;
		this->typeOperation = object;
	}
	else if (object == CheckObjectType::Number) {
		this->operation = false;
		this->value = atof(value.c_str());
	}
	else {
		this->operation = false;
		this->value = -1;
	}
}

OperationObject::~OperationObject()
{
}

double OperationObject::getValue()
{
	return this->value;
}

bool OperationObject::isOperation()
{
	return this->operation;
}

CheckObjectType::ObjectType OperationObject::getOperationType()
{
	if (operation == true) {
		return typeOperation;
	}
	return CheckObjectType::Unknown;
}

void OperationObject::setNewValue(double newValue)
{
	this->operation = false;
	this->value = newValue;
	this->typeOperation = CheckObjectType::Number;
}

void OperationObject::updateToAddition() {
	this->operation = true;
	this->value = -1;
	this->typeOperation = CheckObjectType::AdditionSign;
}
