#include "EquationOperator.h"

EquationOperator::EquationOperator()
{
}

EquationOperator::EquationOperator(std::list<OperationObject*> listOperation)
{
	this->listOperation = listOperation;
}

EquationOperator::~EquationOperator()
{
}

double EquationOperator::operate()
{
	int indexOperator = -1;
	std::cout << "For the equation \"" << this->createStringOperation() << "\" : " << std::endl;
	while ((indexOperator = findIndexOfNextOperator()) >= 0) {
		double subResult = resolveOperationWithIndexOfOperator(indexOperator);
		this->updateListAfterOperation(indexOperator, subResult);
	}
	return this->listOperation.front()->getValue();
}

int EquationOperator::findIndexOfNextOperator()
{
	int savedIndex = -1;
	int i = 0;

	std::list<OperationObject*>::iterator it = this->listOperation.begin();
	for (it; it != listOperation.end(); ++it) {
		if ((*it)->isOperation()) {
			switch ((*it)->getOperationType()) {
			case CheckObjectType::DivisionSign:
				savedIndex = i;
				break;
			case CheckObjectType::MultiplicationSign:
				savedIndex = i;
			default:
				break;
			}
		}
		i++;
	}
	if (savedIndex >= 0)
		return savedIndex;
	i = 0;
	it = this->listOperation.begin();
	for (it; it != listOperation.end(); ++it) {
		if ((*it)->isOperation()) {
			switch ((*it)->getOperationType()) {
			case CheckObjectType::AdditionSign:
				savedIndex = i;
				break;
			case CheckObjectType::SubstractionSign:
				savedIndex = i;
			default:
				break;
			}
		}
		i++;
	}
	return savedIndex;
}

double EquationOperator::resolveOperationWithIndexOfOperator(int indexOperator)
{
	if (indexOperator > this->listOperation.size()) {
		std::cout << "Error: Operator cannot be a the end !" << std::endl;
		throw Exception();
	}

	double result = 0.0;

	std::list<OperationObject*>::iterator it = this->listOperation.begin();
	std::advance(it, indexOperator);
	OperationObject *operatorSign = *it;
	it = this->listOperation.begin();
	std::advance(it, indexOperator - 1);
	OperationObject *nb1 = *it;
	it = this->listOperation.begin();
	std::advance(it, indexOperator + 1);
	OperationObject *nb2 = *it;

	switch (operatorSign->getOperationType()) {
	case CheckObjectType::AdditionSign:
		result = this->makeAddition(nb1->getValue(), nb2->getValue());
		break;
	case CheckObjectType::DivisionSign:
		result = this->makeDivision(nb1->getValue(), nb2->getValue());
		break;
	case CheckObjectType::MultiplicationSign:
		result = this->makeMultiplication(nb1->getValue(), nb2->getValue());
		break;
	case CheckObjectType::SubstractionSign:
		result = this->makeSubstraction(nb1->getValue(), nb2->getValue());
		break;
	default:
		break;
	}
	return result;
}

void EquationOperator::updateListAfterOperation(int indexOperator, double lastResult) {
	std::list<OperationObject*>::iterator it = this->listOperation.begin();

	std::advance(it, indexOperator - 1);
	it = this->listOperation.erase(it);
	it = this->listOperation.erase(it);
	(*it)->setNewValue(lastResult);
}

double EquationOperator::makeAddition(double nb1, double nb2)
{
	return nb1 + nb2;
}

double EquationOperator::makeSubstraction(double nb1, double nb2)
{
	return nb1 - nb2;
}

double EquationOperator::makeDivision(double nb1, double nb2)
{
	if (nb2 > 0) {
		return nb1 / nb2;
	}
	return 0.0;
}

double EquationOperator::makeMultiplication(double nb1, double nb2)
{
	return nb1 * nb2;
}

std::string EquationOperator::createStringOperation()
{
	std::string calculDisplay = "";
	std::list<OperationObject*>::iterator it = this->listOperation.begin();
	for (it; it != listOperation.end(); ++it) {
		if ((*it)->isOperation()) {
			switch ((*it)->getOperationType())
			{
			case CheckObjectType::AdditionSign:
				calculDisplay += "+";
				break;
			case CheckObjectType::DivisionSign:
				calculDisplay += "/";
				break;
			case CheckObjectType::MultiplicationSign:
				calculDisplay += "*";
				break;
			case CheckObjectType::SubstractionSign:
				calculDisplay += "-";
				break;
			default:
				break;
			}
		}
		else {
			calculDisplay += " ";
			std::stringstream ss;
			ss << (*it)->getValue();
			std::string str = ss.str();
			calculDisplay += str;
			calculDisplay += " ";
		}
	}
	return calculDisplay;
}
