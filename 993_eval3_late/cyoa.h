#include <stdio.h>
#include <stdlib.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
class page {
 public:
  int num;
  std::string text;
  std::map<int, std::string> choices;
  std::vector<int> choiceOrder;
  std::map<int, int> pageChoice;
  page(int x) : num(x) {}
};

class story {
 public:
  std::vector<page *> totalStory;
  std::map<int, char> pageType;
  std::set<int> choicePage;
  int winNum;
  int loseNum;
  story(int x = 0, int y = 0) : winNum(x), loseNum(y) {}
};
story * readStory(char ** argv);
void deleteStory(story * Story);
void display(story * Story);
void checkStory(story * Story);
void playStory(story * Story);
void displayPage(story * Story, int pageNum);
int toNum(std::string s);
void winWay(story * Story);
