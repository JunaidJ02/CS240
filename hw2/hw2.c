/*
 * Name: Junaid Javed, hw2.c, CS24000, Fall 2020
 * Last updated Sep 16, 2020
 */

/* Add any includes here */

#include "hw2.h"
#include <stdio.h>
#include <string.h>

/*
 * Define get_month_sold function here
 */

int get_month_sold(char *in_file, int month, int year) {
  char name[MAX_NAME_LEN];
  char area[MAX_AREA_LEN];
  int price = 0;
  int total_price = 0;
  int number_of_houses_match_criteria = 0;
  int dd = 0;
  int mm = 0;
  int yyyy = 0;

  if ((year < 0) || (month < 1) || (month > 12)) {
    return BAD_DATE;
  }

  FILE *fptr = NULL;
  fptr = fopen(in_file, "r");

  if (fptr == NULL) {
    return FILE_READ_ERROR;
  }

  int number_of_values = fscanf(fptr, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                                name, area, &price, &dd, &mm, &yyyy);

  if (number_of_values == 0) {
    return NO_DATA_POINT;
  }

  while (number_of_values == 6) {
    if ((yyyy < 0) || (mm < 1) || (mm > 12) || (dd < 1) || (dd > 31)) {
      fclose(fptr);
      fptr = NULL;
      return BAD_DATE;
    }

    if ((mm == month) && (yyyy == year)) {
      total_price += price;
      number_of_houses_match_criteria++;
    }

    number_of_values = fscanf(fptr, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                              name, area, &price, &dd, &mm, &yyyy);
  }

  fclose(fptr);
  fptr = NULL;

  if ((number_of_values > 0) && (number_of_values != 6)) {
    return BAD_RECORD;
  }

  if (number_of_houses_match_criteria == 0) {
    return NO_DATA_POINT;
  }

  return total_price;

  } /* get_month_sold() */

/*
 *  Define get_max_sold function here
 */

int get_max_sold(char *in_file) {
  char name[MAX_NAME_LEN];
  char area[MAX_AREA_LEN];
  int price = 0;
  int max_price = 0;
  int number_of_houses_match_criteria = 0;
  int dd = 0;
  int mm = 0;
  int yyyy = 0;

  FILE *fptr = NULL;
  fptr = fopen(in_file, "r");

  if (fptr == NULL) {
    return FILE_READ_ERROR;
  }

  int number_of_values = fscanf(fptr, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                                name, area, &price, &dd, &mm, &yyyy);

  if (number_of_values == EOF) {
    fclose(fptr);
    return NO_DATA_POINT;
  }

  while (number_of_values == 6) {
    if ((yyyy < 0) || (mm < 1) || (mm > 12) || (dd < 1) || (dd > 31)) {
      fclose(fptr);
      fptr = NULL;
      return BAD_DATE;
    }

    if (price > max_price) {
      max_price = price;
      number_of_houses_match_criteria++;
    }

    number_of_values = fscanf(fptr, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                              name, area, &price, &dd, &mm, &yyyy);
  }

  if ((number_of_values > 0) && (number_of_values != 6)) {
    fclose(fptr);
    fptr = NULL;
    return BAD_RECORD;
  }

  fclose(fptr);
  fptr = NULL;

  if ((number_of_values > 0) && (number_of_values != 6)) {
    return BAD_RECORD;
  }

  if (number_of_houses_match_criteria == 0) {
    return NO_DATA_POINT;
  }

  return max_price;

} /* get_max_sold() */

/*
 * Define get_auction_list function here
 */

int get_auction_list(char *in_file, char *out_file, int cutoff) {
  char name[MAX_NAME_LEN];
  char area[MAX_AREA_LEN];
  int price = 0;
  int dd = 0;
  int mm = 0;
  int yyyy = 0;
  int number_of_auctions = 0;

  FILE *fptr_in = NULL;
  fptr_in = fopen(in_file, "r");

  if (fptr_in == NULL) {
    return FILE_READ_ERROR;
  }

  FILE *fptr_out = NULL;
  fptr_out = fopen(out_file, "w");

  if (fptr_out == NULL) {
    fclose(fptr_in);
    fptr_in = NULL;
    return FILE_WRITE_ERROR;
  }

  if (cutoff < 0) {
    fclose(fptr_in);
    fptr_in = NULL;
    fclose(fptr_out);
    fptr_out = NULL;
    return BAD_CUTOFF;
  }

  int number_of_values = fscanf(fptr_in, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                                name, area, &price, &dd, &mm, &yyyy);
  while (number_of_values == 6) {
    if ((yyyy < 0) || (mm < 1) || (mm > 12) || (dd < 1) || (dd > 31)) {
      fclose(fptr_in);
      fptr_in = NULL;
      fclose(fptr_out);
      fptr_out = NULL;
      return BAD_DATE;
    }

    if (price > cutoff) {
      fprintf(fptr_out, "Name: %s, Area: %s, Price: %d, %d/%d/%d.\n",
              name, area, price, dd, mm, yyyy);
      number_of_auctions++;
    }

    number_of_values = fscanf(fptr_in, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                              name, area, &price, &dd, &mm, &yyyy);
  }

  fclose(fptr_in);
  fptr_in = NULL;
  fclose(fptr_out);
  fptr_out = NULL;

  if ((number_of_values > 0) && (number_of_values != 6)) {
    return BAD_RECORD;
  }

  if (number_of_auctions == 0) {
    return NO_DATA_POINT;
  }

  return number_of_auctions;
} /* get_auction_list() */

/*
 * Define compare_price function here
 */

int compare_price(char *in_file, char *in_file_2, char *out_file, int month,
                    int year) {
  char name[MAX_NAME_LEN];
  char area[MAX_AREA_LEN];
  int price = 0;
  int total_price_in_file_one = 0;
  int total_price_in_file_two = 0;
  int number_of_houses_in_file_one = 0;
  int number_of_houses_in_file_two = 0;
  int difference = 0;
  int dd = 0;
  int mm = 0;
  int yyyy = 0;

  FILE *fptr_in = NULL;
  fptr_in = fopen(in_file, "r");

  if (fptr_in == NULL) {
    return FILE_READ_ERROR;
  }

  FILE *fptr_in_2 = NULL;
  fptr_in_2 = fopen(in_file_2, "r");

  if (fptr_in_2 == NULL) {
    fclose(fptr_in);
    fptr_in = NULL;
    return FILE_READ_ERROR;
  }

  if ((month < 0) || (month > 12) || (year < 0)) {
    fclose(fptr_in);
    fptr_in = NULL;
    fclose(fptr_in_2);
    fptr_in_2 = NULL;
    return BAD_DATE;
  }

  int number_of_values = fscanf(fptr_in, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                                name, area, &price, &dd, &mm, &yyyy);

  if (number_of_values == 0) {
    fclose(fptr_in);
    fptr_in = NULL;
    fclose(fptr_in_2);
    fptr_in_2 = NULL;
    return NO_DATA_POINT;
  }

  while (number_of_values == 6) {
    if ((yyyy < 0) || (mm < 1) || (mm > 12) || (dd < 1) || (dd > 31)) {
      fclose(fptr_in);
      fptr_in = NULL;
      fclose(fptr_in_2);
      fptr_in_2 = NULL;
      return BAD_DATE;
    }
    if ((mm == month) && (yyyy == year)) {
      total_price_in_file_one += price;
      number_of_houses_in_file_one++;
    }

    number_of_values = fscanf(fptr_in, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                              name, area, &price, &dd, &mm, &yyyy);
  }

  fclose(fptr_in);
  fptr_in = NULL;

  if ((number_of_values > 0) && (number_of_values != 6)) {
    fclose(fptr_in_2);
    fptr_in_2 = NULL;
    return BAD_RECORD;
  }

  if (number_of_houses_in_file_one == 0) {
    fclose(fptr_in_2);
    fptr_in_2 = NULL;
    return NO_DATA_POINT;
  }

  number_of_values = fscanf(fptr_in_2, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                            name, area, &price, &dd, &mm, &yyyy);

  if (number_of_values == 0) {
    fclose(fptr_in_2);
    fptr_in_2 = NULL;
    return NO_DATA_POINT;
  }

  while (number_of_values == 6) {
    if ((yyyy < 0) || (mm < 1) || (mm > 12) || (dd < 1) || (dd > 31)) {
      fclose(fptr_in_2);
      fptr_in_2 = NULL;
      return BAD_DATE;
    }

    if ((mm == month) && (yyyy == year)) {
      total_price_in_file_two += price;
      number_of_houses_in_file_two++;
    }

    number_of_values = fscanf(fptr_in_2, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                              name, area, &price, &dd, &mm, &yyyy);
  }

  fclose(fptr_in_2);
  fptr_in_2 = NULL;

  if ((number_of_values > 0) && (number_of_values != 6)) {
    return BAD_RECORD;
  }

  if (number_of_houses_in_file_two == 0) {
    return NO_DATA_POINT;
  }

  FILE *fptr_out = NULL;
  fptr_out = fopen(out_file, "w");

  if (fptr_out == NULL) {
    return FILE_WRITE_ERROR;
  }

  if (total_price_in_file_one > total_price_in_file_two) {
    difference = total_price_in_file_one - total_price_in_file_two;
    fprintf(fptr_out, "%s has more overall sold price by %d than %s in " \
    "%d/%d", in_file, difference, in_file_2, month, year);
  }
  else if (total_price_in_file_two > total_price_in_file_one) {
    difference = total_price_in_file_two - total_price_in_file_one;
    fprintf(fptr_out, "%s has more overall sold price by %d than %s in " \
    "%d/%d", in_file_2, difference, in_file, month, year);
  }
  else {
    fprintf(fptr_out, "%s and %s have the same overall sold price in " \
    "%d/%d.\n", in_file, in_file_2, month, year);
  }

  fclose(fptr_out);
  fptr_out = NULL;

  return difference;
} /* compare_price() */

/*
 *  Define get_area_average function here
 */

float get_area_average(char *in_file, char *area) {
  char name[MAX_NAME_LEN];
  char file_area[MAX_AREA_LEN];
  int price = 0;
  float total_price = 0.0;
  float average_price = 0.0;
  float number_of_houses = 0.0;
  int dd = 0;
  int mm = 0;
  int yyyy = 0;

  if ((in_file == NULL) || (area == NULL)) {
    return NO_DATA_POINT;
  }

  FILE *fptr = NULL;
  fptr = fopen(in_file, "r");

  if (fptr == NULL) {
    return FILE_READ_ERROR;
  }

  int number_of_values = fscanf(fptr, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                                name, file_area, &price, &dd, &mm, &yyyy);

  while (number_of_values == 6) {
    if ((yyyy < 0) || (mm < 1) || (mm > 12) || (dd < 1) || (dd > 31)) {
      fclose(fptr);
      fptr = NULL;
      return BAD_DATE;
    }
    if (strcmp(file_area, area) == 0) {
      total_price += price;
      number_of_houses++;
    }
    number_of_values = fscanf(fptr, "%40[^,],%40[^,],%d,%2d,%2d,%4d\n",
                              name, file_area, &price, &dd, &mm, &yyyy);
  }

  fclose(fptr);
  fptr = NULL;

  if ((number_of_values > 0) && (number_of_values != 6)) {
    return BAD_RECORD;
  }

  if (number_of_houses == 0) {
    return NO_DATA_POINT;
  }

  average_price = (total_price / number_of_houses);
  return average_price;

} /* get_area_average() */

/* Remember, you don't need a main function!
 * It is provided by hw2_main.c or hw2_test.o.
 */