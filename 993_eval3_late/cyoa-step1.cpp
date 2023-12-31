#include "cyoa.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Wrong input number" << std::endl;
    exit(EXIT_FAILURE);
  }
  story * Story = readStory(argv);
  display(Story);
  deleteStory(Story);
}
