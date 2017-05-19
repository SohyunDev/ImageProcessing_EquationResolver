#include "CheckObjectType.h"

CheckObjectType::CheckObjectType(bool withLog = false)
{
	this->withLog = withLog;
}


CheckObjectType::~CheckObjectType()
{
}

CheckObjectType::ObjectType CheckObjectType::checkObject(EquationObject *picture)
{
	if (checkPropHor(picture)) {
		log("It's just a -");
		return ObjectType::SubstractionSign;
	}
	if (checkBottomLeft(picture)) {
		if (checkRight(picture)) {
			if (checkLeft(picture)) {
				if (checkMiddle(picture)) {
					log("It's just a 8");
					return ObjectType::Eight;
				}
				else {
					log("It's just a 0");
					return ObjectType::Zero;
				}
			}
			else {
				log("It's just a 3");
				return ObjectType::Three;
			}
		}
		else {
			if (checkLeft(picture)) {
				log("It's just a 6");
				return ObjectType::Six;
			}
			else if (checkCollumnLeftTop(picture)) {
				log("It's just a 5");
				return ObjectType::Five;
			}
			else if (checkTopLeft(picture)) {
				if (checkTop(picture)) {
					log("It's just a 2");
					return ObjectType::Two;
				}
				else {
					log("It's just a *");
					return ObjectType::MultiplicationSign;
				}
			}
			else {
				log("It's just a /");
				return ObjectType::DivisionSign;
			}
		}
	}
	else if (checkMiddleLeft(picture)) {
		if (checkTopLeft(picture)) {
			if (checkTop(picture)) {
				log("It's just a 9");
				return ObjectType::Nine;
			}
			else {
				log("It's just a 4");
				return ObjectType::Four;
			}
		}
		else {
			log("It's just a +");
			return ObjectType::AdditionSign;
		}
	}
	else {
		if (checkPropVert(picture)) {
			log("It's just a 1");
			return ObjectType::One;
		}
		else {
			log("It's just a 7");
			return ObjectType::Seven;
		}
	}
	return ObjectType::Unknown;
}

bool CheckObjectType::checkBottomLeft(EquationObject *picture)
{
	return this->checkApproxAround(picture, 1, picture->getHeight() - 2);
}

bool CheckObjectType::checkTop(EquationObject *picture) {
	return checkLine(picture, 0);
}

bool CheckObjectType::checkMiddleLeft(EquationObject *picture)
{
	return checkApproxAround(picture, 1, picture->getHeight() / 2);
}

bool CheckObjectType::checkTopLeft(EquationObject *picture)
{
	return checkApproxAround(picture, 1, 1);
}

bool CheckObjectType::checkPropVert(EquationObject *picture)
{
	if (picture->getWidth() <= picture->getHeight() / 2) {
		return true;
	}
	return false;
}

bool CheckObjectType::checkRight(EquationObject *picture)
{
	return checkCollumn(picture, picture->getWidth() - 3);
}

bool CheckObjectType::checkLeft(EquationObject *picture)
{
	return checkCollumn(picture, 0);
}

bool CheckObjectType::checkMiddle(EquationObject *picture)
{
	return checkApproxAround(picture, picture->getWidth() / 2, picture->getHeight() / 2);
}

bool CheckObjectType::checkCollumnLeftTop(EquationObject *picture)
{
	for (int x = 0; x < 3; x++) {
		bool lineFill = true;
		for (int y = 0; y < picture->getHeight() / 2; y++) {
			Color color = picture->getColorAtIndex(x, y);
			if (color.getBlueColor() > 50) {
				lineFill = false;
			}
		}
		if (lineFill == true) {
			return true;
		}
	}
	return false;
}

bool CheckObjectType::checkPropHor(EquationObject *picture)
{
	if (picture->getHeight() < picture->getWidth() / 3)
		return true;
	return false;
}

bool CheckObjectType::checkApproxAround(EquationObject *picture, int x, int y) {
	for (int y2 = y - 1; y2 < (y + 2); y2++) {
		for (int x2 = x - 1; x2 < (x + 2); x2++) {
			Color color = picture->getColorAtIndex(x2, y2);
			if (color.getBlueColor() < 50) {
				return true;
			}
		}
	}
	return false;
}

bool CheckObjectType::checkLine(EquationObject *picture, int y)
{
	for (int y2 = y; y2 < (y + 2); y2++) {
		bool lineFill = true;
		for (int x = 0; x < picture->getWidth(); x++) {
			Color color = picture->getColorAtIndex(x, y2);
			if (color.getBlueColor() > 50) {
				lineFill = false;
			}
		}
		if (lineFill == true) {
			return true;
		}
	}
	return false;
}

bool CheckObjectType::checkCollumn(EquationObject *picture, int x) {
	for (int x2 = x; x2 < (x + 3); x2++) {
		bool lineFill = true;
		for (int y = 0; y < picture->getHeight(); y++) {
			Color color = picture->getColorAtIndex(x2, y);
			if (color.getBlueColor() > 50) {
				lineFill = false;
			}
		}
		if (lineFill == true) {
			return true;
		}
	}
	return false;
}

void CheckObjectType::log(std::string text)
{
	if (this->withLog) {
		std::cout << text << std::endl;
	}
}
