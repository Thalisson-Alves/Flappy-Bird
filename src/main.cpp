#include <iostream>
#include "Application.h"

int main()
{
	try {
		Application app;
		app.run();
	}
	catch (std::exception& e) {
		std::cout << "EXCEPTION: " << e.what() << '\n';
	}

	return 0;
}
