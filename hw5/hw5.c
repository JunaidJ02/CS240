/* Junaid Javed, hw5.c, CS24000, Fall 2020
 * Last updated Oct 7, 2020
 */

/* Add any includes here */

#include "hw5.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * read_professor will look in the file which has a pointer of file_pointer, the
 * function will read the file and return the nth_professor in the file. It will
 * return the professor in terms of professor_t
 */

professor_t read_professor(FILE *file_pointer, int nth_professor) {

  // Assertions
  assert(file_pointer != NULL);
  assert(nth_professor >= 0);

  // Get the size of the file.
  fseek(file_pointer, 0L, SEEK_END);
  int sz = ftell(file_pointer);

  // Move to the beginning of the file.
  

  /*
   * If the size of the file is less than the the number of the professor we
   * are looking times the size of all professors, then we know that their are
   * less than n professors in this file.
   */
  if (sz < (nth_professor * sizeof(professor_t))) {
    return BAD_PROFESSOR;
  }


  // iterate through the file n times until we reach the nth_professor
  professor_t professor = BAD_PROFESSOR;
  for (int i = 0; i <= nth_professor; i++) {
    assert(fread(&professor, sizeof(professor_t), 1,
                   file_pointer) < sizeof(professor_t));
  }

  return professor;
} /* read_professor() */

/*
 * Write professor takes in a professor_t called professor and writes in the
 * the nth position of the file_pointer. It will return OK or an error if one
 * occurs
 */

int write_professor(FILE * file_pointer, professor_t professor,
                     int nth_professor) {

  // Assertions
  assert(file_pointer != NULL);
  assert(nth_professor >= 0);
  assert(strcmp(professor.first_name, "") != 0);
  assert(strcmp(professor.last_name, "") != 0);
  assert(professor.id_number >= 0);
  assert((professor.gender == MALE) || (professor.gender == FEMALE) ||
           (professor.gender == OTHER));
  assert(professor.age > 0);
  assert(professor.funding > 0);
  for (int day = 0; day < N_DAYS; day++) {
    for (int hour = 0; hour < N_HOURS; hour++) {
      assert((professor.class[day][hour] == 'Y') ||
               (professor.class[day][hour] == 'N'));
    }
  }

  // Get the size of the file.
  fseek(file_pointer, 0L, SEEK_END);
  int sz = ftell(file_pointer);

  // Move to the beginning of the file.
  fseek(file_pointer, 0, SEEK_SET);

  /*
   * If the size of the file is less than the the number of the professor we
   * are looking times the size of all professors, then we know that their are
   * less than n professors in this file.
   */

  if (sz < (nth_professor * sizeof(professor_t))) {
    return WRITE_ERROR;
  }

  professor_t read_professor = BAD_PROFESSOR;
  for (int i = 0; i < nth_professor; i++){
    assert(fread(&read_professor, sizeof(professor_t), 1,
                   file_pointer) < sizeof(professor_t));
  }

  assert(fwrite(&professor, sizeof(professor_t), 1,
                 file_pointer) < sizeof(professor_t));
  return OK;

} /* write_professor() */

/*
 * computer_female_precent finds the number of female professors compared to the
 * total number of professors in the file. It will reutrn the ratio in terms of
 * a number between 0.0 and 1.0.
 */

float compute_female_percent(FILE * file_pointer) {

  // Assertions
  assert(file_pointer != NULL);

  // Move to the beginning of the file.
  fseek(file_pointer, 0, SEEK_SET);

  float total_professors = 0.0;
  float female_professors = 0.0;
  professor_t professor = BAD_PROFESSOR;

  /*
   * While we haven't reached the end, iterate through the file add add one
   * to female_professors if the professor is a female and always add one to
   * total_professors.
   */
  do {
    assert(fread(&professor, sizeof(professor_t), 1,
                   file_pointer) < sizeof(professor_t));
    if (professor.gender == FEMALE) {
      female_professors++;
    }
    total_professors++;
  } while ((!feof(file_pointer)));

  // The last professor is read in twice, so we must account for the duplication
  total_professors--;
  if (professor.gender == FEMALE) {
    female_professors--;
  }


  return (female_professors / total_professors);
} /* compute_female_percent() */

/*
 * total_funding_by_male finds the number of total funding for every professor
 * in the file. It will return the total funding.
 */

float total_funding_by_male(FILE * file_pointer) {

  // Assertions
  assert(file_pointer != NULL);

  // Move to the beginning of the file.
  fseek(file_pointer, 0, SEEK_SET);

  float total_sum = 0.0;
  professor_t professor = BAD_PROFESSOR;

  /*
   * While we haven't reached the end, iterate through the file and add
   * professor.funding to total_sum if the professor is a male.
   */
  do {
    assert(fread(&professor, sizeof(professor_t), 1,
                   file_pointer) < sizeof(professor_t));
    if (professor.gender == MALE) {
      total_sum += professor.funding;
    }
  } while ((!feof(file_pointer)));

  // The last professor is read in twice, so we must account for the duplication
  if (professor.gender == MALE) {
    total_sum -= professor.funding;
  }

  return (total_sum);
} /* total_funding_by_male() */

/*
 * find_professor_by_name will go through every professor in the file until it
 * finds a professor that has the same first name as the argument first_name and
 * the same last name as the argument last_name. It will return the index of the
 * professor.
 */

int find_professor_by_name(FILE * file_pointer, char * first_name,
                             char * last_name) {

  // Assertions
  assert(file_pointer != NULL);
  assert(strcmp(first_name, "") != 0);
  assert(strcmp(last_name, "") != 0);

  // Move to the beginning of the file.
  fseek(file_pointer, 0, SEEK_SET);

  int index = 0;
  professor_t professor = BAD_PROFESSOR;

  /*
   * While we haven't reached the end, iterate through the file until we find
   * a professor who has the same first and last name as the arguemnts, then
   * return the index of that professor right away.
   */
  do {
    assert(fread(&professor, sizeof(professor_t), 1,
                   file_pointer) < sizeof(professor_t));
    if (strcmp(professor.first_name, first_name) == 0) {
      if (strcmp(professor.last_name, last_name) == 0) {
        return index;
      }
    }
    index++;
  } while ((!feof(file_pointer)));

  /*
   * If we iterated through the entire file without return an index, then there
   * is no professor that matches the criteria.
   */
  return NO_PROFESSOR;
} /* find_professor_by_name() */

/*
 * find_professor_by_name will go through every professor in the file until it
 * finds a professor that has the same id number as the argument id_number. It
 * will return the index of the professor.
 */

int find_professor_by_id(FILE * file_pointer, int id_number) {

  // Assertions
  assert(file_pointer != NULL);
  assert(id_number > 0);

  // Move to the beginning of the file.
  fseek(file_pointer, 0, SEEK_SET);

  int index = 0;
  professor_t professor = BAD_PROFESSOR;

  /*
   * While we haven't reached the end, iterate through the file until we find
   * a professor who has the same id number as the arguemnt, then return the
   * index of that professor right away.
   */
  while (!feof(file_pointer)) {
    assert(fread(&professor, sizeof(professor_t), 1,
                   file_pointer) < sizeof(professor_t));
    if (professor.id_number == id_number) {
      return index;
    }
    index++;
  }

  /*
   * If we iterated through the entire file without return an index, then there
   * is no professor that matches the criteria.
   */
  return NO_PROFESSOR;
} /* find_professor_by_id() */

/*
 * average_funding_by_age will iterate through the file and find every professor
 * which is older than the arugment age. It will then find the average amount of
 * funding that these professors have. It will return the average funding.
 */

float average_funding_by_age(FILE * file_pointer, int age) {

  // Assertions
  assert(file_pointer != NULL);
  assert(age > 0);

  // Move to the beginning of the file.
  fseek(file_pointer, 0, SEEK_SET);

  float total_funding = 0.0;
  float total_professors = 0.0;
  professor_t professor = BAD_PROFESSOR;

  /*
   * While we haven't reached the end, iterate through the file until we find
   * a professor who is older than the arguemnt age, then we add their funding
   * to total_funding and increment total_professors by one.
   */
  while (!feof(file_pointer)) {
    assert(fread(&professor, sizeof(professor_t), 1,
                   file_pointer) < sizeof(professor_t));

    if (professor.age > age) {
      total_funding += professor.funding;
      total_professors++;
    }
  }

  // The last professor is read in twice, so we must account for the duplication
  if (professor.age > age) {
    total_funding -= professor.funding;
    total_professors--;
  }

  /*
   * If we iterated through the entire file without finding a professor, then
   * there are no professors that matches the criteria.
   */
  if (total_professors <= 0.0) {
    return NO_PROFESSOR;
  }

  return (total_funding / total_professors);
} /* average_funding_by_age() */

/*
 * fund_student will iterate through the file and find the professor which has
 * the same id number as the arugument id_number. It will then remove $10,000
 * from the porfessors funding in order to fund the student. It will then write
 * to the file and update the file to match the new fudning. It will return OK
 * if successful or an error if one occurs.
 */

int fund_student(FILE * file_pointer, int id_number) {

  // Assertions
  assert(file_pointer != NULL);
  assert(id_number > 0);

  // Move to the beginning of the file.
  fseek(file_pointer, 0, SEEK_SET);

  int index = 0;
  professor_t professor = BAD_PROFESSOR;

  /*
   * While we haven't reached the end, iterate through the file until we find
   * a professor who has the same id number as the arguemnt, then we remove
   * $10,000 from that professors funding and update it by writing the new
   * professor to the same file at the same position
   */
  while (!feof(file_pointer)) {
    assert(fread(&professor, sizeof(professor_t), 1,
                   file_pointer) < sizeof(professor_t));
    if (professor.id_number == id_number) {
      if (professor.funding < 10000.0) {
        return NO_FUNDING;
      } else {
        professor.funding -= 10000.0;
        write_professor(file_pointer, professor, index);
        return OK;
      }
    }
    index++;
  }

  /*
   * If we iterated through the entire file without finding a professor, then
   * there are no professor that matches the criteria.
   */
  return NO_PROFESSOR;
} /* fund_student() */

/*
 * schedule_meeting will iterate through the file and find a professor who has
 * the same id number as the argument professor1_id_number and another
 * professor who has the same id as the argument professor2_id_number. It will
 * then find the first available time that both of these professors are free
 * according to their schedules are return the value (day * 100) + hour.
 */

int schedule_meeting(FILE * file_pointer, int professor1_id_number,
                       int professor2_id_number) {

  // Assertions
  assert(file_pointer != NULL);
  assert(professor1_id_number > 0);
  assert(professor2_id_number > 0);

  // Move to the beginning of the file.
  fseek(file_pointer, 0, SEEK_SET);

  professor_t current_professor = BAD_PROFESSOR;
  professor_t professor1 = BAD_PROFESSOR;
  professor_t professor2 = BAD_PROFESSOR;
  int professors_found = 0;

  /*
   * While we haven't reached the end, iterate through the file until we find
   * a both professors who have the same id number as the arguemnts.
   */
  while (!feof(file_pointer)) {
    assert(fread(&current_professor, sizeof(professor_t), 1,
                   file_pointer) < sizeof(professor_t));
    if (current_professor.id_number == professor1_id_number) {
      professor1 = current_professor;
      professors_found++;
    } else if (current_professor.id_number == professor2_id_number) {
      professor2 = current_professor;
      professors_found++;
    }
  }

  /*
   * Now we iterate through the times of both professors until we find a time
   * where both professors have an 'N' meaning they are free and return that.
   */
  for (int day = 0; day < N_DAYS; day++) {
    for (int hour = 0; hour < N_HOURS; hour++) {
      if ((professor1.class[day][hour] == 'N') &&
             (professor2.class[day][hour] == 'N')) {
        return ((day * 100) + (hour + 8));
      }
    }
  }

  /*
   * If we iterated through the entire file without finding both professors,
   * then there are no professors that matches the criteria.
   */
  if (professors_found != 2) {
    return NO_PROFESSOR;
  }

  /*
   * If we found both professors but did not return a value yet, there there is
   * no overlap.
   */
  return NO_OVERLAP;
} /* schedule_meeting() */
