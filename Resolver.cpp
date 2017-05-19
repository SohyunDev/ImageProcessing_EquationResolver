#include "Resolver.h"

Resolver::Resolver(bool withLog)
{
	this->withLog = withLog;
	this->compare = new CheckObjectType(false); /* true = big log */
}

Resolver::~Resolver()
{
	delete (this->compare);
}

std::string Resolver::newEquation(EquationPicture *picture)
{
	log("Cutting the picture ...");
	this->cutter = new EquationPictureCutter(picture, this->withLog);

	log("Resolve the equation ...");
	double resultNb = this->resolve(); // Main function
	
	/* ========= Convertion double to string ================== */
	std::ostringstream strs;
	strs << resultNb;
	std::string result = strs.str();
	/* ========================================================= */
	
	delete (this->cutter);

	log("End of resolution !");
	return result;
}

double Resolver::resolve() {
	EquationObject* object = NULL;
	std::list<OperationObject*> listOperation;

	while (1) {
		std::string nb = "";
		CheckObjectType::ObjectType operation = CheckObjectType::Unknown;

		while ((object = this->cutter->getNextEquationObject()) != NULL) {
			log("Get next object and compare...");
			CheckObjectType::ObjectType typeObject = this->compare->checkObject(object);
			if (typeObject >= 20 && typeObject != CheckObjectType::Unknown) {
				log("Operation sign found !");
				operation = typeObject;
				break;
			}
			else if (typeObject != CheckObjectType::Unknown) {
				log("Number found !");
				std::stringstream ss;
				ss << typeObject;
				nb += ss.str();
			}
			else {
				log("Unknown sign found !");
			}
		}
		log("Update list of operation ...");
		if (listOperation.size() > 0 && listOperation.back()->isOperation() && listOperation.back()->getOperationType() == CheckObjectType::SubstractionSign) {
			listOperation.back()->updateToAddition();
			std::string tmp = "-";
			tmp += nb;
			nb = tmp;
		}
		listOperation.push_back(new OperationObject(CheckObjectType::Number, nb));
		if (operation != CheckObjectType::Unknown)
			listOperation.push_back(new OperationObject(operation, ""));
		else {
			break;
		}
	}
	log("All object compared ! Resolve the equation ...");
	/*std::string calculString = this->createStringOperation(listOperation);
	std::cout << "Operation looks like : " + calculString << std::endl;*/
	EquationOperator *operationResolver = new EquationOperator(listOperation);
	double result = operationResolver->operate();
	delete operationResolver;

	std::list<OperationObject*>::iterator it = listOperation.begin();
	for (it; it != listOperation.end(); ++it) {
		delete * it;
		listOperation.erase(it);
	}
	return result;
}

void Resolver::log(std::string text)
{
	if (this->withLog) {
		std::cout << text << std::endl;
	}
}
