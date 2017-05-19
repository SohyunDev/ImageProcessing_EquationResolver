#pragma once

#include "opencv2\core\core.hpp"

using namespace cv;

class Color // RGBQUAD equivalent
{
private:
	short red;
	short green;
	short blue;

public:
	// Define using Vec3s
	Color(Vec3s);
	Color();
	~Color();
	short getRedColor();
	short getBlueColor();
	short getGreenColor();
	void setRedColor(short);
	void setBlueColor(short);
	void setGreenColor(short);
};

