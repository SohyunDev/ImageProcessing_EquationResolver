#include "LabelPoints.h"

Point LabelPoint::getPointAtIndex(int index) {
	return this->point.at(index);
}

void LabelPoint::pushPoint(Point point) {
	this->point.push_back(point);
	this->num++;
}

int LabelPoint::getNum() {
	return this->num;
}

void LabelPoint::setNumZero() {
	this->num = 0;
}

void LabelPoint::clearPoint() {
	this->point.clear();
}

std::vector<Point> LabelPoint::getPoints() {
	return this->point;
}

void LabelPoint::setIndex(short index) {
	this->index = index;
}

short LabelPoint::getIndex() {
	return this->index;
}
LabelPoint LabelPoints::getLabelPointAtIndex(int index) {
	return this->points.at(index);
}

void LabelPoints::pushPoints(LabelPoint labelpoint) {
	this->points.push_back(labelpoint);
	this->num++;
}

int LabelPoints::getNum() {
	return this->num;
}

std::vector<LabelPoint> LabelPoints::getPoints() {
	return this->points;
}