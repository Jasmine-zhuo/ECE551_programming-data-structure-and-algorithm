#include "cyoa.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input number");
  }
  story * Story = readStory_step4(argv);
  playStory_step4(Story);
  deleteStory(Story);
  return EXIT_SUCCESS;
}
