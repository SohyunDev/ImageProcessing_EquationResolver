#include "EquationPictureCutter.h"


EquationPictureCutter::EquationPictureCutter(EquationPicture* picture, bool withLog) // cut the entire picture into small ones
{
	/* Basic init */
	this->withLog = withLog;
	this->currentObject = 0;
	/*----*/


	log("Grayscaling the picture ...");
	picture->Grayscaling();
	log("Binarization the picture ...");
	picture->Binarization();


	// Load EquationPoints
	log("Labeling the picture ...");
	std::vector<EqPoint> eqpoints = picture->Labeling_SendCutPoints();
	log("Done");
	
	int width, height;
	Point p1, p2;
	Color color;
	for (int i = 0; i < eqpoints.size(); i++) {
		p1 = eqpoints.at(i).getP1();
		p2 = eqpoints.at(i).getP2();
		width = p2.x - p1.x + 1;
		height = p2.y - p1.y + 1;
		log("New object found");
		EquationObject* obj = new EquationObject(width, height);

		// Set Color
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				color = picture->getColorAtIndex(p1.x + x, p1.y + y);
				obj->setColorAtIndex(x, y, color);
			}
		}

		/* BIG LOG */
		//log("Object looks like : ");
		//log(obj);
		/* END BIG LOG */

		// push object
		this->objects.push_back(obj);
		log("Object saved");
		// if you don't want to show cut images, make comment below
		
		Mat img = obj->getPicture();
		imshow("Test", img);
		waitKey(0);
		
	}
	log("All objects found");
}


void EquationPictureCutter::log(std::string text)
{
	if (this->withLog) {
		std::cout << text << std::endl;
	}
}

void EquationPictureCutter::log(EquationObject *object)
{
	if (this->withLog) {
		object->printLogObject();
	}
}

EquationPictureCutter::~EquationPictureCutter()
{
	log("Deleting EquationPictureCutter");
	std::list<EquationObject*>::iterator it = this->objects.begin();
	for (it; it != this->objects.end(); ++it) {
		delete * it;
		this->objects.erase(it);
	}
}

EquationObject* EquationPictureCutter::getNextEquationObject()
{
	if (this->objects.size() <= this->currentObject) {
		return NULL;
	}
	std::list<EquationObject*>::iterator it = this->objects.begin();
	std::advance(it, this->currentObject);
	this->currentObject++;
	return *it;
}


int EquationPictureCutter::getCurrentObject() {
	return this->currentObject;
}
