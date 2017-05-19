#include "EquationPicture.h"

EquationPicture::EquationPicture(String picturePath) : EquationObject()
{
	this->picture = imread(picturePath);
	if (!picture.data) {
		std::cout << "ERROR: image path doesn't exist !" << std::endl;
		throw Exception();
	}
	else {
		this->width = picture.cols;
		this->height = picture.rows;
	}
}


EquationPicture::~EquationPicture()
{
}

void EquationPicture::Grayscaling() {
	Color color, dstcolor;
	short gray;
	for (int y = 0; y < this->getHeight(); y++) {
		for (int x = 0; x < this->getWidth(); x++) {
			color = this->getColorAtIndex(x, y);
			gray = (color.getBlueColor() + color.getGreenColor() + color.getRedColor()) / 3;
			dstcolor = Color({ gray, gray, gray });
			this->setColorAtIndex(x, y, dstcolor);
		}
	}
}

void EquationPicture::Binarization() {
	Color color;
	short black = 0, white = 255;
	short threshold = 100;
	for (int y = 0; y < this->getHeight(); y++) {
		for (int x = 0; x < this->getWidth(); x++) {
			color = this->getColorAtIndex(x, y);
			if (color.getBlueColor() > threshold) {
				this->setColorAtIndex(x, y, Color({ white, white, white }));
			}
			else {
				this->setColorAtIndex(x, y, Color({ black,black,black }));
			}
		}
	}
}

std::vector<EqPoint> EquationPicture::Labeling_SendCutPoints() {
	int width = this->getWidth();
	int height = this->getHeight();
	int max = 0, labelIndex = 0, label = 1;

	EquationObject newpicture = EquationObject(width, height);
	short* table = new short[height*width];
	Color color;
	Point point;
	Stack stack;
	LabelPoint labelpoint = LabelPoint();
	LabelPoints labelpoints = LabelPoints();
	
	int labelingCnt[9999] = { 0, };
	int found[100] = { 0, };
	int foundnum = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			color = this->getColorAtIndex(x, y);
			table[y*width + x] = color.getRedColor();
		}
	}

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (!table[y*width + x]) {
				stack.push(Point(x, y));
				table[y*width + x] = label;
				labelpoint.pushPoint(Point(x, y));
				labelpoint.setIndex(label);
			}
			else {
				continue;
			}

			// Make labeling (eight direction)
			while (!stack.isEmpty()) {
				point = stack.pop();
				labelingCnt[label]++;
				// right
				if ((point.x < width - 1) && (!table[point.y*width + point.x + 1])) {
					table[point.y*width + point.x + 1] = label;
					stack.push(Point(point.x + 1, point.y));
					labelpoint.pushPoint(Point(point.x + 1, point.y));
				}
				//left
				if ((point.x > 0) && (!table[point.y*width + point.x - 1])) {
					table[point.y * width + point.x - 1] = label;
					stack.push(Point(point.x - 1, point.y));
					labelpoint.pushPoint(Point(point.x - 1, point.y));
				}
				//up
				if ((point.y > 0) && (!table[(point.y - 1)*width + point.x])) {
					table[(point.y - 1)*width + point.x] = label;
					stack.push(Point(point.x, point.y - 1));
					labelpoint.pushPoint(Point(point.x, point.y - 1));
				}
				//down
				if ((point.y < height - 1) && (!table[(point.y + 1)*width + point.x])) {
					table[(point.y + 1)*width + point.x] = label;
					stack.push(Point(point.x, point.y + 1));
					labelpoint.pushPoint(Point(point.x, point.y + 1));
				}
				// leftup
				if ((point.x > 0) && (point.y > 0) && (!table[(point.y - 1)*width + point.x - 1])) {
					table[(point.y - 1)*width + point.x - 1] = label;
					stack.push(Point(point.x - 1, point.y - 1));
					labelpoint.pushPoint((Point(point.x - 1, point.y - 1)));
				}
				// right up
				if ((point.x < width - 1) && (point.y - 1 > 0) && (!table[(point.y - 1)*width + point.x + 1])) {
					table[(point.y - 1)*width + point.x + 1] = label;
					stack.push(Point(point.x + 1, point.y - 1));
					labelpoint.pushPoint(Point(point.x + 1, point.y - 1));
				}
				// left down
				if ((point.x > 0) && (point.y < height - 1) && (!table[(point.y + 1)*width + point.x - 1])) {
					table[(point.y + 1)*width + point.x - 1] = label;
					stack.push(Point(point.x - 1, point.y + 1));
					labelpoint.pushPoint(Point(point.x - 1, point.y + 1));
				}
				// right down
				if ((point.x < width - 1) && (point.y < height - 1) && (!table[(point.y + 1)*width + point.x + 1])) {
					table[(point.y + 1)*width + point.x + 1] = label;
					stack.push(Point(point.x + 1, point.y + 1));
					labelpoint.pushPoint(Point(point.x + 1, point.y + 1));
				}
			}
			label++;
			labelpoints.pushPoints(labelpoint);
			
			// Clear LabelPoint
			labelpoint.clearPoint();
			labelpoint.setNumZero();
		}
	}

	// find rectangle
	LabelPoint foundrect = LabelPoint();
	Point rectpoint1, rectpoint2;
	for (int i = 0; i < labelpoints.getNum(); i++) {
		Point point;
		Point p1 = labelpoints.getLabelPointAtIndex(i).getPointAtIndex(0), p2 = labelpoints.getLabelPointAtIndex(i).getPointAtIndex(0);
		// Number of Labeled points : range ( 1000 ~ )
		if (labelpoints.getLabelPointAtIndex(i).getNum() >= 1000) {
			for (int j = 0; j < labelpoints.getLabelPointAtIndex(i).getNum(); j++) {
				point = labelpoints.getLabelPointAtIndex(i).getPointAtIndex(j);
				if (point.x < p1.x) {
					p1.x = point.x;
				}
				if (point.y < p1.y) {
					p1.y = point.y;
				}
				if (point.x > p2.x) {
					p2.x = point.x;
				}
				if (point.y > p2.y) {
					p2.y = point.y;
				}

			}
			double rate = (double)(p2.x - p1.x) / (double)(p2.y - p1.y);
			// ratio of width/height = about 1.5
			// So set rate (1.3 ~ 1.7)
			if (rate > 1.3 && rate<1.7) {
				DrawRect(p1, p2, Color({ 0,0,255 }));
				rectpoint1 = p1;
				rectpoint2 = p2;
				foundrect = labelpoints.getLabelPointAtIndex(i);
			}
		}
	}

	// find equation
	LabelPoints equation = LabelPoints();
	for (int i = 0; i < labelpoints.getNum(); i++) {
		// Ignore when number of Labeled Point is too small (more than 5)
		if (labelpoints.getLabelPointAtIndex(i).getNum() >= 5) {
			Point point = labelpoints.getLabelPointAtIndex(i).getPointAtIndex(0);
			if (point.x > rectpoint1.x && point.x < rectpoint2.x
				&& point.y > rectpoint1.y && point.y < rectpoint2.y) {
				equation.pushPoints(labelpoints.getLabelPointAtIndex(i));
			}
		}
	}

	// Store CutPoints (left&uppermost, right&lowermost)
	std::vector<EqPoint> cutpoints;
	// temporary cutpoint to push
	EqPoint cutpoint = EqPoint();

	// save equationPoints
	for (int i = 0; i < equation.getNum(); i++) {

		Point p1 = equation.getLabelPointAtIndex(i).getPointAtIndex(0), p2 = equation.getLabelPointAtIndex(i).getPointAtIndex(0);
		for (int j = 0; j < equation.getLabelPointAtIndex(i).getNum(); j++) {
			point = equation.getLabelPointAtIndex(i).getPointAtIndex(j);
			if (point.x < p1.x) {
				p1.x = point.x;
			}
			if (point.y < p1.y) {
				p1.y = point.y;
			}
			if (point.x > p2.x) {
				p2.x = point.x;
			}
			if (point.y > p2.y) {
				p2.y = point.y;
			}
		}
		cutpoint.SetPoints(p1, p2);
		cutpoints.push_back(cutpoint);
	}

	return cutpoints;

}


void EquationPicture::DrawRect(Point p1, Point p2, Color color) {
	int width = this->getWidth();
	int height = this->getHeight();

	int y1 = (p1.y - 2 > 0) ? p1.y - 2 : 0;
	int y2 = (p2.y + 2 < height) ? p2.y + 2 : height;
	int x1 = (p1.x - 2 > 0) ? p1.x - 2 : 0;
	int x2 = (p2.x + 2 < width) ? p2.x + 2 : width;

	for (int y = y1; y < y2; y++) {
		for (int x = x1; x < x2; x++) {
			if ((((y > p1.y + 2) || (y < p2.y - 2)) && ((x < p1.x + 2) || (x > p2.x - 2))) || (y < p1.y + 2) || (y > p2.y - 2)) {
				this->setColorAtIndex(x, y, color);
			}
		}
	}
}
