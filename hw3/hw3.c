/* Name: Junaid Javed, hw3.c, CS24000, Fall 2020
 * Last updated Sep 23, 2020
 */
NUfpfin_]|
/* Add any includes here */
#include "hw3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int g_college_count = 0;
char g_college_name[MAX_RECORDS][MAX_COLLEGE_LEN];
int g_student_gender[MAX_RECORDS][GENDER_TYPES];
int g_student_residency[MAX_RECORDS][RESIDENCY_TYPES];
int g_student_accommodation[MAX_RECORDS][ACCOMMODATION_TYPES];

/*
 * Read in_file and store all the text data into array or tables. This function
 * will return the number of colleges stored into its tables
 */

int input_tables(char *in_file) {
  char college_name[MAX_COLLEGE_LEN];
  int female = 0;
  int male = 0;
  int unlisted = 0;
  int international = 0;
  int non_resident = 0;
  int resident = 0;
  int hall = 0;
  int house = 0;
  int apartment = 0;
  int with_parents = 0;

  FILE *fptr = NULL;
  fptr = fopen(in_file, "r");

  if (fptr == NULL) {
    return FILE_READ_ERROR;
  }

  g_college_count = 0;

  int number_of_values = fscanf(fptr, "%39[^;];%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
                                college_name, &female, &male, &unlisted,
                                &international, &non_resident, &resident,
                                &hall, &house, &apartment, &with_parents);

  st

  /*
   * While there are 11 values to read (nothing is malformed),
   * store the data in its alloted array value
   */
  while (number_of_values == 11) {
    strncpy(g_college_name[g_college_count], college_name, 39);
    g_student_gender[g_college_count][0] = female;
    g_student_gender[g_college_count][1] = male;
    g_student_gender[g_college_count][2] = unlisted;
    g_student_residency[g_college_count][0] = international;
    g_student_residency[g_college_count][1] = non_resident;
    g_student_residency[g_college_count][2] = resident;
    g_student_accommodation[g_college_count][0] = hall;
    g_student_accommodation[g_college_count][1] = house;
    g_student_accommodation[g_college_count][2] = apartment;
    g_student_accommodation[g_college_count][3] = with_parents;
    g_college_count++;

    number_of_values = fscanf(fptr, "%39[^;];%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
                                college_name, &female, &male, &unlisted,
                                &international, &non_resident, &resident,
                                &hall, &house, &apartment, &with_parents);
  }

  // If we read a vlue other than 11 but still more than 0, then its malformed
  if ((number_of_values > 0) && (number_of_values != 11)) {
    fclose(fptr);
    fptr = NULL;
    return RECORD_ERROR;
  }

  fclose(fptr);
  fptr = NULL;

  if (g_college_count == 0) {
    return NO_DATA_POINT;
  }

  return g_college_count;
} /* input_tables() */

/*
 * This function returns the number of total students in a certain college that
 * is named college_name
 */

int student_size(char *college_name) {
  int college_name_index = -1;
  int total_students = 0;

  if ((college_name == NULL) || (g_college_count == 0)) {
    return NO_DATA_POINT;
  }

  // Loop throught all the colleges until we find which index is needed
  for (int i = 0; i < g_college_count; i++) {
    if (strcmp(g_college_name[i], college_name) == 0) {
      college_name_index = i;
    }
  }

  if (college_name_index == -1) {
    return NO_SUCH_COLLEGE;
  }

  for (int i = 0; i < GENDER_TYPES; i++) {
    total_students += g_student_gender[college_name_index][i];
  }

  return total_students;
} /* student_size() */

/*
 * Return a float of the ratio of students that live with their parents in
 * certain college name college_name
 */

float live_with_parents_ratio(char *college_name) {
  int college_name_index = -1;
  float total_students = 0.0;
  float students_living_with_parents = 0.0;

  if ((college_name == NULL) || (g_college_count == 0)) {
    return NO_DATA_POINT;
  }

  // Loop throught all the colleges until we find which index is needed
  for (int i = 0; i < g_college_count; i++) {
    if (strcmp(g_college_name[i], college_name) == 0) {
      college_name_index = i;
    }
  }

  if (college_name_index == -1) {
    return NO_SUCH_COLLEGE;
  }

  for (int i = 0; i < GENDER_TYPES; i++) {
    total_students += g_student_gender[college_name_index][i];
  }

  students_living_with_parents = g_student_accommodation[college_name_index][3];
  return (students_living_with_parents / total_students);
} /* live_with_parents_ratio() */

/*
 * Return a float of the ratio of on campus and off campus students in
 * certain college name college_name
 */

float on_off_campus_ratio(char *college_name) {
  int college_name_index = -1;
  float total_on_campus_students = 0.0;
  float total_off_campus_students = 0.0;

  if ((college_name == NULL) || (g_college_count == 0)) {
    return NO_DATA_POINT;
  }

  // Loop throught all the colleges until we find which index is needed
  for (int i = 0; i < g_college_count; i++) {
    if (strcmp(g_college_name[i], college_name) == 0) {
      college_name_index = i;
    }
  }

  if (college_name_index == -1) {
    return NO_SUCH_COLLEGE;
  }

  total_on_campus_students = g_student_accommodation[college_name_index][0];

  for (int i = 1; i < 3; i++) {
    total_off_campus_students += g_student_accommodation[college_name_index][i];
  }

  return (total_on_campus_students / total_off_campus_students);
} /* on_off_campus_ratio() */

/*
 * Return a float of the ratio of female and male students at Purdue University
 */

float gender_ratio(void) {
  float female_students = 0.0;
  float male_students = 0.0;

  if (g_college_count == 0) {
    return NO_DATA_POINT;
  }

  for (int i = 0; i < g_college_count; i++) {
    female_students += g_student_gender[i][0];
    male_students += g_student_gender[i][1];
  }

  printf("Ratio: %f\n", female_students / male_students);
  return (female_students / male_students);
} /* gender_ratio() */

/*
 * Find the college that has the most students and retrurn the index at which
 * it is located
 */

int max_student_size(void) {
  int total_students = 0;
  int max_students = 0;
  int max_students_college_index = 0;

  if (g_college_count == 0) {
    return NO_DATA_POINT;
  }

  for (int i = 0; i < g_college_count; i++) {
    total_students += g_student_gender[i][0] +
                      g_student_gender[i][1] + g_student_gender[i][2];

    if (total_students > max_students) {
      max_students = total_students;
      max_students_college_index = i;
    }
    total_students = 0;
  }

  return (max_students_college_index);
} /* max_student_size() */

/*
 * Find the college that has the biggest international to total student ratio
 * and return the index for where it is located
 */

int max_international_percent(void) {
  float total_students = 0;
  float international_students = 0;
  float ratio = 0.0;
  float max_ratio = 0.0;
  int max_ratio_college_index = 0;

  if (g_college_count == 0) {
    return NO_DATA_POINT;
  }

  for (int i = 0; i < g_college_count; i++) {
    total_students += g_student_gender[i][0] +
                      g_student_gender[i][1] + g_student_gender[i][2];

    international_students = g_student_residency[i][0];
    ratio = international_students / total_students;

    if (ratio > max_ratio) {
      max_ratio = ratio;
      max_ratio_college_index = i;
    }
    total_students = 0;
    international_students = 0;
  }

  return (max_ratio_college_index);
} /* max_international_percent() */

/*
 *  Print the college name, nubmer of students, number of intl. students,
 *  number of students in resident halls, and number of studnets with parents
 *  from index start to index end into a file called out_file. Return OK if no
 *  errors occur, or an error code.
 */

int output_tables(char *out_file, int start, int end) {
  char college_name[MAX_COLLEGE_LEN];
  int number_of_students = 0;
  int number_of_international_students = 0;
  int number_of_students_in_resident_halls = 0;
  int number_of_students_with_parents = 0;

  if (g_college_count == 0) {
    return NO_DATA_POINT;
  }

  if ((start < 0) || (start > g_college_count) || (end < 0 )
      || (end > g_college_count) || (end < start)) {
    return OUT_OF_BOUNDS;
  }

  FILE *fptr_out = NULL;
  fptr_out = fopen(out_file, "w");

  if (fptr_out == NULL) {
    return FILE_WRITE_ERROR;
  }

  for (int i = start; i <= end; i++) {
    strncpy(college_name, g_college_name[i], 39);
    number_of_students = g_student_gender[i][0] +
                               g_student_gender[i][1] + g_student_gender[i][2];
    number_of_international_students = g_student_residency[i][0];
    number_of_students_in_resident_halls = g_student_accommodation[i][0];
    number_of_students_with_parents = g_student_accommodation[i][3];

    fprintf(fptr_out, "%s;%d;%d;%d;%d\n", college_name, number_of_students,
            number_of_international_students,
            number_of_students_in_resident_halls,
            number_of_students_with_parents);
  }

  fclose(fptr_out);
  fptr_out = NULL;
  return OK;

} /* output_tables() */

/* Remember, you don't need a main function!
 * It is provided by hw3_main.c or hw3_test.o.
 */