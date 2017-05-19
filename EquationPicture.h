#pragma once

#include <iostream>

#include "Stack.h"

using namespace cv;

class EquationPicture : public EquationObject // cximage equivalent
{
public:
	EquationPicture() {};
	EquationPicture(String);
	~EquationPicture();
	// Make gray
	void Grayscaling();
	// Make binary
	void Binarization();
	// Labeling and send cutpoints
	std::vector<EqPoint> Labeling_SendCutPoints();

	// It will not needed I made this to recognize rectangle
	void DrawRect(Point, Point, Color);
};

