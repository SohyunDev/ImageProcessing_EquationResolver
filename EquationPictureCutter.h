#pragma once
#include "EquationPicture.h"

class EquationPictureCutter // Adjust and cut picture into object picture ("1 + 2 + 3" = "1" "+" "2" "+" "3")
{
private:
	std::list<EquationObject*> objects; // This is the list of each object picture ("1" "+" "2" "+" "3")
	int currentObject;
	bool withLog;
	void log(std::string);
	void log(EquationObject*);

public:
	EquationPictureCutter(EquationPicture*, bool = false); // Cut function, not implemented \!/
	~EquationPictureCutter();
	EquationObject* getNextEquationObject(); // Give the next object picture ("1" next "+" next "2" next "+" next "3", ...)
	int getCurrentObject();
};

