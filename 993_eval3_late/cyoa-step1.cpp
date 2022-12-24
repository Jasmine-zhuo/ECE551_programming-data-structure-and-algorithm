#include "cyoa.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input number");
  }

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
  story Story;
  while (std::getline(f, line)) {
    line += "\n";
    //std::cout << line;
    if (line[0] == '\n' || line[0] == ' ') {
      continue;
    }
    size_t at_index = line.find('@');
    if (at_index != std::string::npos) {                   //declaration lines
      std::string pageNum_str = line.substr(0, at_index);  //find page number
      int pageNum = std::atoi(pageNum_str.c_str());
      page * p = new page(pageNum);
      std::ostringstream ss;
      std::ifstream curPage;

      std::string path = std::string(argv[1]) + "/page" + pageNum_str + ".txt";
      //std::cout << path << std::endl;
      curPage.open(path.c_str());
      if (curPage.fail()) {
        std::cerr << "An error occured when opening a page file!" << std::endl;
        exit(EXIT_FAILURE);
      }
      ss << curPage.rdbuf();
      p->text = ss.str();
      Story.pageType[pageNum] = line[at_index + 1];
      Story.totalStory.push_back(p);
      if (size_t(p->num) != (Story.totalStory.size() - 1)) {
        std::cerr << "Pages do not appear in order." << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    else {  //choice lines
      size_t col_index_1 = line.find(':');
      std::string pageNum_str = line.substr(0, col_index_1);
      size_t col_index_2 = line.find(':', col_index_1 + 1);
      std::string choiceNum_str = line.substr(col_index_1 + 1, col_index_2);
      int pageNum = std::atoi(pageNum_str.c_str());
      int choiceNum = std::atoi(choiceNum_str.c_str());
      std::string choice = line.substr(col_index_2 + 1);
      Story.totalStory[pageNum]->choices[choiceNum] = choice;
      Story.totalStory[pageNum]->choiceOrder.push_back(choiceNum);
    }
  }
  //for declaration line test
  for (std::vector<page *>::iterator it = Story.totalStory.begin();
       it != Story.totalStory.end();
       it++) {
    std::cout << "Page " << (*it)->num << std::endl;
    std::cout << "==========\n";
    std::cout << (*it)->text << std::endl;
    if (Story.pageType[(*it)->num] == 'N') {
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
    else if (Story.pageType[(*it)->num] == 'W') {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (Story.pageType[(*it)->num] == 'L') {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    delete (*it);
  }

  //end for declaration line test
}
