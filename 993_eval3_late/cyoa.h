#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class page {
 public:
  int num;
  std::string text;
  std::map<int, std::string> choices;
  std::vector<int> choiceOrder;
  page(int x) : num(x) {}
};

class story {
 public:
  std::vector<page *> totalStory;
  std::map<int, char> pageType;
};
