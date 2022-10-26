/*
# -------------------- #
# (C)2022 madoodia.com #
# -------------------- #
*/

// Standard Libraries
#include <iostream>

// Third Party Libraries

// Application Libraries
#include "core.h"
#include "api2.h"
#include "api/api.h"
#include "nolib.h"
#include "mydll.h"

// Main Function
int main()
{
  std::cout << "Result: " << Madoodia::add(10, 20) << std::endl;
  std::cout << "Result: " << Madoodia::sub(10, 3) << std::endl;
  std::cout << "Result: " << Madoodia2::add2(100, 200) << std::endl;
  std::cout << "Result: " << Madoodia3::mult(100, 200) << std::endl;
  return 0;
}
