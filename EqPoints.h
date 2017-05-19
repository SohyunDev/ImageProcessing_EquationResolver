#include "opencv2\core\core.hpp"

using namespace cv;

// store eqation Point
class EqPoint {
private:
	// p1 : leftmost & highest
	// p2 : rightmost & lowest
	Point p1, p2;

public:
	EqPoint() {};
	EqPoint(Point, Point);
	~EqPoint() {};
	void SetPoints(Point, Point);
	Point getP1();
	Point getP2();
};
