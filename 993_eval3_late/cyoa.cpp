#include "cyoa.h"
story * readStory(char ** argv) {
  std::string line;
  std::string dir(argv[1]);
  dir += "/story.txt";
  //FILE * f = fopen(dir.c_str(), "r");
  std::ifstream f;
  f.open(dir.c_str());
  if (f.fail()) {
    std::cerr << "An error occured when opening a story.txt file!" << std::endl;
    exit(EXIT_FAILURE);
  }
  story * Story = new story();
  while (std::getline(f, line)) {
    line += "\n";
    if (line[0] == '\n' || line[0] == ' ') {
      continue;
    }  //ignore blank lines
    size_t at_index = line.find('@');
    if (at_index != std::string::npos) {                   //declaration lines
      std::string pageNum_str = line.substr(0, at_index);  //find page number
      int pageNum = std::atoi(pageNum_str.c_str());
      page * p = new page(pageNum);
      std::ostringstream ss;
      std::ifstream curPage;

      std::string path = std::string(argv[1]) + "/" +
                         line.substr(at_index + 3, line.size() - at_index - 4);
      curPage.open(path.c_str());  //open page file
      if (curPage.fail()) {
        std::cerr << "An error occured when trying to open this file:" << path
                  << std::endl;
        exit(EXIT_FAILURE);
      }
      ss << curPage.rdbuf();
      p->text = ss.str();  //fill page text
      char curType = line[at_index + 1];
      Story->pageType[pageNum] = curType;
      if (curType == 'W') {
        Story->winNum++;
      }
      if (curType == 'L') {
        Story->loseNum++;
      }
      Story->totalStory.push_back(p);
      if (size_t(p->num) != (Story->totalStory.size() - 1)) {
        std::cerr << "Pages do not appear in order." << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    else {  //choice lines
      size_t col_index_1 = line.find(':');
      std::string pageNum_str = line.substr(0, col_index_1);  //get page number
      size_t col_index_2 = line.find(':', col_index_1 + 1);
      std::string choiceNum_str =
          line.substr(col_index_1 + 1, col_index_2);  //get choice page number
      int pageNum = std::atoi(pageNum_str.c_str());
      int choiceNum = std::atoi(choiceNum_str.c_str());
      std::string choice = line.substr(col_index_2 + 1);  //get choice message
      if (Story->pageType.find(pageNum) == Story->pageType.end()) {
        std::cerr << "This page does not exist, cannot add choice pages!" << std::endl;
        exit(EXIT_FAILURE);
      }
      Story->totalStory[pageNum]->choices[choiceNum] = choice;
      Story->totalStory[pageNum]->choiceOrder.push_back(choiceNum);
      Story->choicePage.insert(choiceNum);
    }
  }
  //for declaration line test
  return Story;
}
void display(story * Story) {
  for (std::vector<page *>::iterator it = Story->totalStory.begin();
       it != Story->totalStory.end();
       it++) {
    std::cout << "Page " << (*it)->num << std::endl;
    std::cout << "==========\n";
    std::cout << (*it)->text << std::endl;
    if (Story->pageType[(*it)->num] == 'N') {
      std::cout << "What would you like to do?" << std::endl << std::endl;
      int i = 1;
      for (std::vector<int>::iterator it1 = (*it)->choiceOrder.begin();
           it1 != (*it)->choiceOrder.end();
           it1++) {
        std::cout << ' ' << i << ". ";
        i++;
        std::cout << (*it)->choices[*it1];
      }
    }
    else if (Story->pageType[(*it)->num] == 'W') {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (Story->pageType[(*it)->num] == 'L') {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
  }
}

void deleteStory(story * Story) {
  for (std::vector<page *>::iterator it = Story->totalStory.begin();
       it != Story->totalStory.end();
       ++it) {
    delete (*it);
  }
  delete Story;
}

void checkStory(story * Story) {
  for (std::set<int>::iterator it = Story->choicePage.begin();
       it != Story->choicePage.end();
       ++it) {
    if (Story->pageType.find(*it) != Story->pageType.end()) {  //choice page is valid
      // std::cout << "Page" << (*it) << " is a valid choice page" << std::endl;
    }
    else {
      std::cerr << "Error! Page" << (*it) << "is not a valid choice page" << std::endl;
      deleteStory(Story);
      exit(EXIT_FAILURE);
    }
  }
  if (Story->choicePage.find(0) != Story->choicePage.end()) {  //Page 0 is referneced
    if (Story->choicePage.size() !=
        Story->totalStory
            .size()) {  //every page(except 0) is referenced by at least 1 other page
      std::cerr << "There exist page(s) which are not references by other pages"
                << std::endl;
      deleteStory(Story);
      exit(EXIT_FAILURE);
    }
  }
  else {
    if (Story->choicePage.size() !=
        Story->totalStory.size() -
            1) {  //every page(except 0) is referenced by at least 1 other page
      std::cerr << "There exist page(s) which are not references by other pages"
                << std::endl;
      deleteStory(Story);
      exit(EXIT_FAILURE);
    }
  }
  if (Story->winNum <= 0) {
    std::cerr << "There must be at least 1 win page!" << std::endl;
    deleteStory(Story);
    exit(EXIT_FAILURE);
  }
  if (Story->loseNum <= 0) {
    std::cerr << "There must be at least 1 lose page!" << std::endl;
    deleteStory(Story);
    exit(EXIT_FAILURE);
  }

  //std::cout << "Story was successfully checked!" << std::endl;
}
void displayPage(story * Story, int pageNum) {
  page * Page = Story->totalStory[pageNum];
  std::cout << "Page " << pageNum << std::endl;
  std::cout << "==========\n";
  std::cout << Page->text << std::endl;
  if (Story->pageType[pageNum] == 'N') {
    std::cout << "What would you like to do?" << std::endl << std::endl;
    int i = 1;
    for (std::vector<int>::iterator it1 = Page->choiceOrder.begin();
         it1 != Page->choiceOrder.end();
         it1++) {
      std::cout << ' ' << i << ". ";
      i++;
      std::cout << Page->choices[*it1];
    }
  }
  else if (Story->pageType[Page->num] == 'W') {
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    deleteStory(Story);
    exit(EXIT_SUCCESS);
  }
  else if (Story->pageType[Page->num] == 'L') {
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    deleteStory(Story);
    exit(EXIT_SUCCESS);
  }
}
int toNum(std::string s) {
  size_t i = 0;
  while (i < s.size()) {
    if (s[i] != ' ') {
      break;
    }
    i++;
  }
  if (i == s.size()) {  //s="(' ')*"
    return -1;
  }
  if (s[i] == '0') {  //s = "(' ')*0"
    return (i == s.size() - 1) ? 0 : -1;
  }
  int sum = 0;
  size_t j = 0;
  for (j = i; j < s.size(); j++) {
    if (s[j] < '0' || s[j] > '9') {
      break;
    }
    else {
      int cur_digit = s[j] - '0';
      sum = 10 * sum + cur_digit;
    }
  }

  return (j == s.size()) ? sum : (-1);
}
void playStory(story * Story) {
  std::string in_str;
  displayPage(Story, 0);
  int cur_pageNUM = 0;
  while (std::cin >> in_str) {
    int num = toNum(in_str);
    if (num == 0 || num == -1 ||
        (size_t)num > Story->totalStory[cur_pageNUM]->choiceOrder.size()) {
      std::cout << "That is not a valid choice, please try again";
      continue;
    }
    cur_pageNUM = Story->totalStory[cur_pageNUM]->choiceOrder[num - 1];
    displayPage(Story, cur_pageNUM);
  }
}
