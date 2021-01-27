/* Homework 3 Main function
 * CS 240 - Fall 2020
 * Last updated Sep 14, 2020
 */

#include "hw3.h"

#include <stdio.h>

/*
 * This function is used to check the input
 */

int clean_stdin()
{
  while (getchar() != '\n') {
  }
  return (1);
} /* clean_stdin() */

/*
 * This function is used to print the return value for different functions
 */

void print_return_value(int val, char * function) {
  printf("The value returned by the %s() was: %d ", function, val);
  switch (val) {
    case FILE_READ_ERROR:
      printf("(FILE_READ_ERROR)\n");
      break;
    case FILE_WRITE_ERROR:
      printf("(FILE_WRITE_ERROR)\n");
      break;
    case RECORD_ERROR:
      printf("(RECORD_ERROR)\n");
      break;
    case OUT_OF_BOUNDS:
      printf("(OUT_OF_BOUNDS)\n");
      break;
    case NO_SUCH_COLLEGE:
      printf("(NO_SUCH_COLLEGE)\n");
      break;
    case NO_DATA_POINT:
      printf("(NO_DATA_POINT)\n");
      break;
    default:
      printf("\n");
      break;
  }
} /* print_return_value() */

/*  This function is used to run the functions implemented in hw3.c.
 *  User input is used to determine which function to run what input
 *  is passed to it. Upon completion, the function returns zero.
 */

int main() {
  char file[1000] = "";
  char college[1000] = "";
  int num = 0;
  int val = 0;
  float float_val = 0;
  int start = 0;
  int end = 0;
  int loaded = 0;
  int read = 0;
  char c = ' ';

  while (1) {
    printf("-----------------------------------------\n");
    printf("0) Quit\n"
           "1) input_tables()\n"
           "2) student_size()\n"
           "3) live_with_parents_ratio()\n"
           "4) on_off_campus_ratio()\n"
           "5) gender_ratio()\n"
           "6) max_student_size()\n"
           "7) max_international_percent()\n"
           "8) output_tables()\n"
           "\nSelect a function: ");

    read = scanf("%d%c", &num, &c);
    while (((read != 2) || (c != '\n')) && (clean_stdin())) {
      printf("Wrong input!\n");
      printf("Select a function: ");
      read = scanf("%d%c", &num, &c);
    }
    if ((num > 8) || (num < 0)) {
      printf("Wrong selection. \n");
      continue;
    }

    if (num == 0) {
      printf("Goodbye!~\n");
      break;
    }

    if ((num != 1) && (loaded == 0)) {
      printf("You tables are not loaded, please load your tables first.\n");
      continue;
    }

    if (num > 8) {
      printf("Invalid selection.\n");
      continue;
    }

    if (num == 0) {
      return 0;
    }

    if ((num == 1) || (num == 8)) {
      printf("Enter the file name: ");
      scanf("%s", file);
    }

    if ((num == 2) || (num == 3) || (num == 4)) {
      printf("Enter the college name: ");
      scanf("\n%[^\n]", college);
    }

    if (num == 8) {
      printf("Enter the starting row index: ");
      read = scanf("%d%c", &start, &c);
      while (((read != 2) || (c != '\n')) && (clean_stdin())) {
        printf("Wrong input!\n");
        printf("Enter the starting row index: ");
        read = scanf("%d%c", &start, &c);
      }
      printf("Enter the ending row index: ");
      read = scanf("%d%c", &end, &c);
      while (((read != 2) || (c != '\n')) && (clean_stdin())) {
        printf("Wrong input!\n");
        printf("Enter the ending row index: ");
        read = scanf("%d%c", &end, &c);
      }
    }

    switch (num) {
      case 1:
        val = input_tables(file);
        print_return_value(val, "input_tables");
        if (val > 0) {
          loaded = 1;
        }
        else {
          loaded = 0;
        }
        break;
      case 2:
        val = student_size(college);
        print_return_value(val, "student_size");
        break;
      case 3:
        float_val = live_with_parents_ratio(college);
        printf("The value returned by the %s() was: %f\n"
               , "live_with_parents_ratio", float_val);
        break;
      case 4:
        float_val = on_off_campus_ratio(college);
        printf("The value returned by the %s() was: %f\n"
               , "on_off_campus_ratio", float_val);
        break;
      case 5:
        float_val = gender_ratio();
        printf("The value returned by the %s() was: %f\n"
               , "gender_ratio", float_val);
        break;
      case 6:
        val = max_student_size();
        print_return_value(val, "max_student_size");
        break;
      case 7:
        val = max_international_percent();
        print_return_value(val, "max_international_percent");
        break;
      case 8:
        val = output_tables(file, start, end);
        print_return_value(val, "output_tables");
        break;
      default:
        break;
    }
  }

  return 0;
} /* main() */

