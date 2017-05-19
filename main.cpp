
#include <string>
#include <iostream>
#include "EquationPicture.h"
#include "Resolver.h"

int main(int argc, char **argv)
{
	Resolver *resolver = NULL;
	std::string picturePath = "";

	if (argc > 1) {
		std::string arg1 = argv[1];
		if (arg1 == "log") {
			resolver = new Resolver(true);
			if (argc > 2) {
				picturePath = argv[2];
			}
			else {
				std::cout << "Enter a picture path for the EquationResolver : ";
				std::getline(std::cin, picturePath);
			}
		}
		else {
			resolver = new Resolver(false);
			picturePath = argv[1];
		}
	}
	else { // ... if not, i ask to write the path of a picture
		resolver = new Resolver(false);
		std::cout << "Enter a picture path for the EquationResolver : ";
		std::getline(std::cin, picturePath);
	}

	while (true) {
		std::cout << std::endl << "Opening file : " << picturePath << std::endl;

		try {
			EquationPicture *picture = new EquationPicture(picturePath);
			std::string result = resolver->newEquation(picture);

			delete(picture);
			std::cout << "Result : " << result << std::endl;
		} catch (Exception e) {
			std::cerr << "Aborted ..." << std::endl;
		}

		 // I give the path of the picture to the resolver, and return a string of the result
		std::cout << std::endl << "=====================================================" << std::endl
			<< "Enter a picture path for the EquationResolver (exit for quit) : ";
		std::getline(std::cin, picturePath);
		if (picturePath == "exit")
			break;
	}
	delete (resolver);
	std::cout << std::endl << "Goodbye !" << std::endl;
	system("pause");
	return 0;
}