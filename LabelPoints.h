#include "opencv2\core\core.hpp"

using namespace cv;

// Labeling Points

// Labeling point
class LabelPoint {
private:
	std::vector<Point> point;
	short index;
	int num = 0;

public:
	LabelPoint() {};
	~LabelPoint() {};
	Point getPointAtIndex(int);			
	void pushPoint(Point);				
	int getNum();						

	// Clear Label Point (clearPoint & setNumZero)
	void clearPoint();					
	void setNumZero();					

	std::vector<Point> getPoints();
	void setIndex(short);
	short getIndex();
};


// Store Labeled Points
class LabelPoints {
private:
	std::vector<LabelPoint> points;
	int num = 0;

public:
	LabelPoints() {};
	~LabelPoints() {};
	LabelPoint getLabelPointAtIndex(int);
	void pushPoints(LabelPoint);
	int getNum();
	std::vector<LabelPoint> getPoints();
};
