/*
# -------------------- #
# (C)2022 madoodia.com #
# -------------------- #
*/

// Standard Libraries
#include <iostream>

// Third Party Libraries

// Application Libraries
#include "api2.h"
#include "core/api.h"

// Main Function
int main()
{
	std::cout << "Result: " << Madoodia::add(10, 20) << std::endl;
	std::cout << "Result: " << Madoodia2::add2(100, 200) << std::endl;
	return 0;
}
