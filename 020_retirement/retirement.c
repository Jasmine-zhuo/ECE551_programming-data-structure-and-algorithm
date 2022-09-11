#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;

  for (int i = startAge; i < working.months + startAge; i++) {
    int year;
    int month;
    year = i / 12;
    month = i - year * 12;
    printf("Age %3d month %2d you have $%.2f\n", year, month, balance);
    balance = balance + (working.rate_of_return * balance) + working.contribution;
  }
  for (int i = startAge + working.months; i < working.months + startAge + retired.months;
       i++) {
    int year;
    int month;
    year = i / 12;
    month = i - year * 12;
    printf("Age %3d month %2d you have $%.2f\n", year, month, balance);
    balance = balance + (retired.rate_of_return * balance) + retired.contribution;
  }
}

int main() {
  int startAge = 327;
  double initial = 21345;
  retire_info retired;
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}
