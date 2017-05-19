#include "EqPoints.h"

EqPoint::EqPoint(Point x, Point y) {
	this->p1 = x;
	this->p2 = y;
}

void EqPoint::SetPoints(Point x, Point y) {
	this->p1 = x;
	this->p2 = y;
}

Point EqPoint::getP1() {
	return p1;
}

Point EqPoint::getP2() {
	return p2;
}
