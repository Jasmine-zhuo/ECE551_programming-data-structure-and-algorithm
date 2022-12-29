#include "cyoa.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input number");
  }
  story * Story = readStory(argv);
  checkStory(Story);
  winWay(Story);
  deleteStory(Story);
  return EXIT_SUCCESS;
}
