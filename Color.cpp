#include "Color.h"

// Vec3s
Color::Color(Vec3s color)
{
	this->blue = color[0];
	this->green = color[1];
	this->red = color[2];
}

Color::Color()
{
	this->blue = 255;
	this->green = 255;
	this->red = 255;
}


Color::~Color()
{
}

short Color::getRedColor()
{
	return this->red;
}

short Color::getBlueColor()
{
	return this->blue;
}

short Color::getGreenColor()
{
	return this->green;
}

void Color::setRedColor(short r) {
	this->red = r;
}

void Color::setBlueColor(short b) {
	this->blue = b;
}

void Color::setGreenColor(short g) {
	this->green = g;
}
