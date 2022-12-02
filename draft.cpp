#include "Basic/Utils/tokenScanner.hpp"
#include <iostream>

int main() {
  TokenScanner s("34abd");
  s.scanNumbers();
  std::cout << s.nextToken();

}

