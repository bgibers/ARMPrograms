#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

std::string to_string(double x);

int main()
{
  double pi = 3.14159;
  std::string str = to_string(pi);

  std::cout << str << std::endl;

  // Cstring:
  char digits[10];
  std::strcpy( digits, str.c_str() );

  std::cout << std::endl << "c-string:" << std::endl;
  std::cout << digits[1] << std::endl;
  std::cout << digits << std::endl;

  return 0;
}

std::string to_string(double x)
{
  std::ostringstream ss;
  ss << x;
  return ss.str();
}
