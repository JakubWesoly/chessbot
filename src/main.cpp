#include "Program.hpp"
#include <iostream>

int main()
{
  try {
    Program::run();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "Unknown error" << std::endl;
    return 1;
  }
  return 0;
}