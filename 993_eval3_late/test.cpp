#include <iostream>
#include <string>

#include "cyoa.h"
int main(void) {
  std::string s;
  while (std::cin >> s) {
    std::cout << s << "," << toNum(s) << std::endl;
  }
  return 0;
}
