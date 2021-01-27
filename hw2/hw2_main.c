/* Homework 2 Main function
 * CS 240 - Fall 2020
 * Last updated Sep 6, 2020
 */

#include "hw2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This function is used to check whether the input
 */

int clean_stdin()
{
  while (getchar() != '\n') {
  }
  return (1);
} /* clean_stdin() */

/*
 * This function is used to run the functions implemented in hw2.c.
 * User input is used to determine which function to run what input
 * is passed to it. Upon completion, the function returns zero.
 */

int main(int argc, char **argv) {
  while (1) {
    printf("====================================================\n");
    printf("Test Menu\n");
    printf("1. get_month_sold()\n");
    printf("2. get_max_sold()\n");
    printf("3. get_auction_list()\n");
    printf("4. compare_price()\n");
    printf("5. get_area_average()\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");

    int response = 0;
    int read = 0;
    char c = ' ';

    read = scanf("%d%c", &response, &c);
    while (((read != 2) || (c != '\n')) && clean_stdin()) {
      printf("Wrong input!\n");
      printf("Enter your choice: ");
      read = scanf("%d%c", &response, &c);
    }

    int month = 0;
    int year = 0;
    int total = 0;
    int max = 0;
    int cutoff = 0;
    float avg = 0;
    int err_code = 0;
    char input_filename[MAX_FILE_LEN] = "";
    char input_filename1[MAX_FILE_LEN] = "";
    char input_filename2[MAX_FILE_LEN] = "";
    char result_filename[MAX_FILE_LEN] = "";
    char area[MAX_AREA_LEN] = "";

    switch (response) {
      case 1:
        printf("Enter input file name: ");
        scanf("%s", input_filename);
        printf("Enter year: ");
        read = scanf("%d%c", &year, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter year: ");
          read = scanf("%d%c", &year, &c);
        }
        printf("Enter month as a number (ex. January -> 1): ");
        read = scanf("%d%c", &month, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter month as a number (ex. January -> 1): ");
          read = scanf("%d%c", &month, &c);
        }
        total = get_month_sold(input_filename, month, year);
        if (total >= 0) {
          printf("get_month_sold(%s, %d, %d) returned %d\n",
              input_filename, month, year, total);
        } else {
          printf("Error! (code %d)\n", total);
        }
        break;

      case 2:
        printf("Enter input file name: ");
        scanf("%s", input_filename);
        max = get_max_sold(input_filename);
        if (max >= 0) {
          printf("get_max_sold(%s) returned %d\n", input_filename, max);
        } else {
          printf("Error! (code %d)\n", max);
        }
        break;

      case 3:
        printf("Enter input file name: ");
        scanf("%s", input_filename);
        printf("Enter output file name: ");
        scanf("%s", result_filename);
        printf("Enter cutoff: ");
        read = scanf("%d%c", &cutoff, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter cutoff: ");
          read = scanf("%d%c", &cutoff, &c);
        }
        err_code = get_auction_list(input_filename, result_filename, cutoff);
        if (err_code >= 0) {
          printf("get_auction_list(%s, %s, %d) returned %d\n",
              input_filename, result_filename, cutoff, err_code);
        } else {
          printf("Error! (code %d)\n", err_code);
        }
        break;

      case 4:
        printf("Enter 1st input file name: ");
        scanf("%s", input_filename1);
        printf("Enter 2nd input file name: ");
        scanf("%s", input_filename2);
        printf("Enter output file name: ");
        scanf("%s", result_filename);
        printf("Enter year: ");
        read = scanf("%d%c", &year, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter year: ");
          read = scanf("%d%c", &year, &c);
        }
        printf("Enter month as a number (ex. January -> 1): ");
        read = scanf("%d%c", &month, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter month as a number (ex. January -> 1): ");
          read = scanf("%d%c", &month, &c);
        }
        err_code = compare_price(input_filename1, input_filename2,
                                      result_filename, month, year);
        if (err_code >= 0) {
          printf("compare_price(%s, %s ,%s, %d, %d) returned %d\n"
                 , input_filename1, input_filename2, result_filename
                 , month, year, err_code);
        } else {
          printf("Error! (code %d)\n", err_code);
        }
        break;

      case 5:
        printf("Enter input file name: ");
        scanf("%s", input_filename);
        printf("Enter area: ");
        scanf("%s", area);
        avg = get_area_average(input_filename, area);
        if (avg >= 0) {
          printf("get_area_average(%s, %s) returned %.4f\n"
                 , input_filename, area, avg);
        } else {
          printf("Error! (code %d)\n", (int)avg);
        }
        break;

      case 6:
        printf("Good Bye :^) \n\n");
        return (0);

      default:
        printf("Invalid choice!\n");
        break;
    }
  }
  return (0);
} /* main() */
