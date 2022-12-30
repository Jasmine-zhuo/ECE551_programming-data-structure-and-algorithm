#include "cyoa.h"
story * readStory(char ** argv) {  //read story by line and store info
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
        deleteStory(Story);
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
        deleteStory(Story);
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
        deleteStory(Story);
        exit(EXIT_FAILURE);
      }
      Story->totalStory[pageNum]->choices[choiceNum] = choice;
      Story->totalStory[pageNum]->choiceOrder.push_back(choiceNum);
      Story->totalStory[pageNum]->pageChoice[choiceNum] =
          Story->totalStory[pageNum]->choiceOrder.size();  //map(page number,choice order)
      Story->choicePage.insert(choiceNum);
    }
  }
  //for declaration line test
  return Story;
}
void display(story * Story) {  //display story in step1
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

void checkStory(story * Story) {  //check story in step2
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
void displayPage(story * Story, int pageNum) {  //display certain page used in step2
  page * Page = Story->totalStory[pageNum];
  //  std::cout << "Page " << pageNum << std::endl;
  //std::cout << "==========\n";
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
int toNum(  //make sure valid input choice and convert string to number in step2
    std::string s) {
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
  //if (s[i] == '0') {  //s = "(' ')*0"
  //return (i == s.size() - 1) ? 0 : -1;
  //}
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
void playStory(story * Story) {  //play story in step2
  std::string in_str;
  displayPage(Story, 0);
  int cur_pageNUM = 0;
  while (std::cin >> in_str) {
    int num = toNum(in_str);
    if (num == 0 || num == -1 ||
        (size_t)num > Story->totalStory[cur_pageNUM]->choiceOrder.size()) {
      std::cout << "That is not a valid choice, please try again\n";
      continue;
    }
    cur_pageNUM = Story->totalStory[cur_pageNUM]->choiceOrder[num - 1];
    displayPage(Story, cur_pageNUM);
  }
}
typedef std::pair<int, std::vector<int> > myPair;
void winWay(story * Story) {  //find cycle-free way to win in step3
  std::queue<std::pair<int, std::vector<int> > > BFS_q;
  std::vector<std::vector<int> > ans;
  myPair p = make_pair(0, std::vector<int>());
  BFS_q.push(p);
  while (!BFS_q.empty()) {
    myPair cur = BFS_q.front();
    cur.second.push_back(cur.first);
    BFS_q.pop();
    if (Story->pageType[cur.first] == 'W') {
      ans.push_back(cur.second);
      continue;
    }
    page * curPage = Story->totalStory[cur.first];
    for (size_t i = 0; i < curPage->choiceOrder.size(); i++) {
      int nextPageNum = curPage->choiceOrder[i];
      size_t j;
      for (j = 0; j < cur.second.size(); j++) {
        if (cur.second[j] == nextPageNum)
          break;
      }
      if (j == cur.second.size()) {
        myPair next = make_pair(nextPageNum, cur.second);
        BFS_q.push(next);
      }
    }
  }
  if (!ans.empty()) {
    for (size_t k = 0; k < ans.size(); k++) {
      for (size_t m = 0; m < ans[k].size() - 1; m++) {
        std::cout << ans[k][m] << "("
                  << Story->totalStory[ans[k][m]]->pageChoice[ans[k][m + 1]] << "),";
      }
      std::cout << ans[k][ans[k].size() - 1];

      std::cout << "(win)" << std::endl;
    }
  }
  else {
    std::cout << "This story is unwinnable!" << std::endl;
  }
}
story * readStory_step4(char ** argv) {
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
    size_t dollar_index = line.find('$');
    size_t bracket_index_1 = line.find('[');

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
        deleteStory(Story);
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
        deleteStory(Story);
        exit(EXIT_FAILURE);
      }
    }
    else if (dollar_index != std::string::npos) {  //set variables
      std::string pageNum_str = line.substr(0, dollar_index);
      int pageNum = std::atoi(pageNum_str.c_str());
      size_t equal_index = line.find('=');
      std::string var = line.substr(dollar_index + 1, equal_index - dollar_index - 1);
      std::string value_str = line.substr(equal_index + 1);
      int value = std::atoi(value_str.c_str());
      if (Story->pageType.find(pageNum) == Story->pageType.end()) {
        std::cerr << "This page does not exist, cannot add variable to this page!"
                  << std::endl;
        deleteStory(Story);
        exit(EXIT_FAILURE);
      }
      Story->variables[var] = 0;
      Story->totalStory[pageNum]->setVar[var] = value;
    }
    else if (bracket_index_1 != std::string::npos) {  //conditional choice lines
      std::string pageNum_str = line.substr(0, bracket_index_1);
      int pageNum = std::atoi(pageNum_str.c_str());
      size_t bracket_index_2 = line.find(']');
      size_t equal_index = line.find('=');
      std::string var =
          line.substr(bracket_index_1 + 1, equal_index - bracket_index_1 - 1);
      std::string value_str =
          line.substr(equal_index + 1, bracket_index_2 - equal_index - 1);
      int value = std::atoi(value_str.c_str());
      size_t col_index_1 = line.find(':');
      size_t col_index_2 = line.find(':', col_index_1 + 1);
      std::string choiceNum_str =
          line.substr(col_index_1 + 1, col_index_2 - col_index_1 - 1);
      int choiceNum = std::atoi(choiceNum_str.c_str());
      std::string choice = line.substr(col_index_2 + 1);
      if (Story->pageType.find(pageNum) == Story->pageType.end()) {
        std::cerr << "This page does not exist, cannot add choice pages!" << std::endl;
        deleteStory(Story);
        exit(EXIT_FAILURE);
      }
      Story->totalStory[pageNum]->choices[choiceNum] = choice;
      Story->totalStory[pageNum]->choiceOrder.push_back(choiceNum);
      Story->totalStory[pageNum]->pageChoice[choiceNum] =
          Story->totalStory[pageNum]->choiceOrder.size();  //map(page number,choice order)
      Story->choicePage.insert(choiceNum);
      std::pair<std::string, int> curVar = std::make_pair(var, value);
      Story->totalStory[pageNum]->Condition[choiceNum] = curVar;
      Story->totalStory[pageNum]->allCondition[choiceNum] = false;
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
        deleteStory(Story);
        exit(EXIT_FAILURE);
      }
      Story->totalStory[pageNum]->choices[choiceNum] = choice;
      Story->totalStory[pageNum]->choiceOrder.push_back(choiceNum);
      Story->totalStory[pageNum]->pageChoice[choiceNum] =
          Story->totalStory[pageNum]->choiceOrder.size();  //map(page number,choice order)
      Story->choicePage.insert(choiceNum);
    }
  }
  //for declaration line test
  return Story;
}
void playStory_step4(story * Story) {
  std::string in_str;
  displayPage_step4(Story, 0);
  int cur_pageNUM = 0;

  while (std::cin >> in_str) {
    /**TEST ONLY BEGINS**/
    /*****************************/
    /*
    std::cout << std::endl << "****************************" << std::endl;
    for (std::map<std::string, int>::iterator it = Story->variables.begin();
         it != Story->variables.end();
         it++) {
      std::cout << it->first << "is now:" << it->second << std::endl;
    }
    std::cout << std::endl << "****************************" << std::endl;
    */
    /****************************/
    /**TEST ONLY ENDS**/

    int num = toNum(in_str);
    if (num == 0 || num == -1 ||
        (size_t)num > Story->totalStory[cur_pageNUM]->choiceOrder.size()) {
      std::cout << "That is not a valid choice, please try again\n";
      continue;
    }

    page * curPage = Story->totalStory[cur_pageNUM];
    int nextPageNum = curPage->choiceOrder[num - 1];
    if (curPage->allCondition.find(nextPageNum) != curPage->allCondition.end() &&
        curPage->allCondition[nextPageNum] ==
            false) {  //choice is conditional and condition not met
      std::cout << "That choice is not available at this time, please try again"
                << std::endl;
      //std::cout << curPage->choicePrompt;
      //display this page and the choices again
      continue;
    }

    cur_pageNUM = nextPageNum;
    displayPage_step4(Story, cur_pageNUM);
  }
}
void displayPage_step4(story * Story, int pageNum) {  //display certain page used in step2
  page * Page = Story->totalStory[pageNum];
  for (std::map<std::string, int>::iterator it =
           Story->totalStory[pageNum]->setVar.begin();
       it != Story->totalStory[pageNum]->setVar.end();
       it++) {  //set variables value for each page
    Story->variables[(*it).first] = (*it).second;
  }
  std::cout << Page->text << std::endl;
  if (Story->pageType[pageNum] == 'N') {
    std::cout << "What would you like to do?" << std::endl << std::endl;
    int i = 1;

    for (std::vector<int>::iterator it1 = Page->choiceOrder.begin();
         it1 != Page->choiceOrder.end();
         it1++) {
      if (Page->Condition.find(*it1) != Page->Condition.end()) {
        std::string curVar = Page->Condition[*it1].first;
        int curValue = Page->Condition[*it1].second;
        if (Story->variables[curVar] == curValue) {  //condition met
          Page->allCondition[(*it1)] = true;
          Page->choicePrompt += " " + int2str(i) + ". " + Page->choices[*it1];

          std::cout << ' ' << i << ". ";
          std::cout << Page->choices[*it1];
          i++;
        }
        else {  //condition not met
                /***********FOR TEST ONLY BEGINS***/
                //std::cout << "This choice requires the variable " << curVar << "to be "
          // << curValue << ", but it is now " << Story->variables[curVar] << std::endl;
          /***********FOR TEST ONLY ENDS****/
          Page->allCondition[(*it1)] = false;
          Page->choicePrompt += " " + int2str(i) + ". " + "<UNAVAILABLE>\n";

          std::cout << ' ' << i << ". ";
          std::cout << "<UNAVAILABLE>" << std::endl;
          i++;
        }
      }
      else {  //not a conditional choice
        Page->choicePrompt += " " + int2str(i) + ". " + Page->choices[*it1];

        std::cout << ' ' << i << ". ";
        std::cout << Page->choices[*it1];
        i++;
      }
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
std::string int2str(int x) {
  std::stringstream ss;
  ss << x;
  return ss.str();
}
