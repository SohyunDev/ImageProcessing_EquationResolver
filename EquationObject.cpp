#include "EquationObject.h"

EquationObject::EquationObject()
{
}

// not EquationObject(int width, int height)
EquationObject::EquationObject(int width, int height) // I don't know if this is functionnal
{
	Mat image(height, width, CV_8UC3, Scalar(0, 0, 0));

	this->picture = image;
	this->width = width;
	this->height = height;
}

EquationObject::~EquationObject()
{
}

int EquationObject::getWidth()
{
	return this->width;
}

int EquationObject::getHeight()
{
	return this->height;
}

Color EquationObject::getColorAtIndex(int x, int y)
{
	if (x >= width || y >= height) {
		return Color();
	}
	Color color(this->picture.at<Vec3b>(Point(x, y)));
	return color;
}

void EquationObject::setColorAtIndex(int x, int y, Color newColor)
{
	Vec3b color = this->picture.at<Vec3b>(Point(x, y));
	color[0] = newColor.getBlueColor();
	color[1] = newColor.getGreenColor();
	color[2] = newColor.getRedColor();
	this->picture.at<Vec3b>(Point(x, y)) = color;
}

void EquationObject::printLogObject()
{
	std::cout << "=====================================================" << std::endl << std::endl;
	std::cout << "WIDTH = " << width << "   HEIGHT = " << height << std::endl << std::endl;;
	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			if (this->getColorAtIndex(x, y).getBlueColor() > 70) {
				std::cout << " ";
			}
			else {
				std::cout << "x";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "=====================================================" << std::endl;
}

Mat EquationObject::getPicture() {
	return this->picture;
}
