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
  int num;                             //page number
  std::string text;                    //page contents
  std::map<int, std::string> choices;  //next page number and corresponding choice string
  std::vector<int> choiceOrder;        //next page numbers
  std::map<int, int> pageChoice;       //next page number and choice number
  std::map<std::string, int> setVar;
  std::map<int, std::pair<std::string, int> > Condition;
  page(int x) : num(x) {}
};

class story {
 public:
  std::vector<page *> totalStory;  //all pages in story
  std::map<int, char> pageType;    //page number and page type
  std::set<int> choicePage;        //next possible pages
  int winNum;                      //win page number
  int loseNum;                     //lose page number
  std::map<std::string, int> variables;
  story(int x = 0, int y = 0) : winNum(x), loseNum(y) {}
};
story * readStory(char ** argv);  //read story by line and store info
void deleteStory(story * Story);
void display(story * Story);                   //display story in step1
void checkStory(story * Story);                //check story in step2
void playStory(story * Story);                 //play story in step2
void displayPage(story * Story, int pageNum);  //display certain page used in step2
int toNum(
    std::string s);  //make sure valid input choice and convert string to number in step2
void winWay(story * Story);  //find cycle-free way to win in step3
story * readStory_step4(char ** argv);
void playStory_step4(story * Story);
void displayPage_step4(story * Story, int pageNum);
