/* HW5 main function
 * Fall 2020, CS2400
 */

#include <string.h>
#include <stdio.h>

#include "hw5.h"

/* function definition*/

professor_t read_professor_from_file(char *);

/*
 * use to read input
 */

int clean_stdin(){
  while (getchar() != '\n') {
  }
  return 1;
} /* clean_stdin() */

/*
 * use to check whether professor is bogus or not
 */

static int compare_bogus(professor_t prof) {
  return ((prof.id_number == -1) &&
    !strcmp(prof.first_name, "BOGUS") &&
    !strcmp(prof.last_name, "BOGUS") &&
    (prof.age == -1) &&
    (prof.funding == -1.0) &&
    (prof.gender == -1) &&
    (prof.class[N_DAYS - 1][N_HOURS - 1] == 'Y'));
} /* compare_bogus() */

/*
 * use to print the information of a professor struct
 */

static void print_professor(professor_t prof) {
  printf("\nID Number: %d\n", prof.id_number);
  printf("First Name: %s\n", prof.first_name);
  printf("Last Name: %s\n", prof.last_name);
  printf("Age: %d\n", prof.age);
  printf("Funding: %.2f\n", prof.funding);
  printf("Gender: ");
  switch (prof.gender) {
    case MALE:
      printf("Male\n");
      break;
    case FEMALE:
      printf("Female\n");
      break;
    case OTHER:
      printf("Other\n");
      break;
    default:
      printf("-1\n");
      break;
  }
  if (!compare_bogus(prof)) {
    printf("Class:");
    for (int day = 0; day < N_DAYS; day++) {
      printf(" ");
      for (int hour = 0; hour < N_HOURS; hour++) {
        printf("%c", prof.class[day][hour]);
      }
    }
    printf("\n");
  }
} /* print_professor() */

/*
 * This function is used to run the different functions implemented in file
 * hw5.c. User input is used to determine which function to run and what input
 * is passed to it. Upon completion, the function returns zero.
 */

int main() {
  char c = ' ';
  int read = 0;

  char database_file[100] = "";
  char prof_file[100] = "";
  char first_name[20] = "";
  char last_name[20] = "";
  FILE * database_fp = 0;
  int age = 0;
  int n = 0;
  int value = 0;
  float f_value = 0;
  int id = 0;
  int id1 = 0;
  int id2 = 0;
  professor_t prof = {0};

  while (1) {

    printf("\nOPTIONS:\n"
           "0) Quit\n"
           "1) read_professor()\n"
           "2) write_professor()\n"
           "3) compute_female_percent()\n"
           "4) total_funding_by_male()\n"
           "5) find_professor_by_name()\n"
           "6) find_professor_by_id()\n"
           "7) average_funding_by_age()\n"
           "8) fund_student()\n"
           "9) schedule_meeting()\n"
           "Select a function: ");
    int choice = 0;
    read = scanf("%d%c", &choice, &c);
    while (((read != 2) || (c != '\n')) && (clean_stdin())) {
      printf("Wrong input!\n");
      printf("Select a function: ");
      read = scanf("%d%c", &choice, &c);
    }
    if (choice == 0) {
      printf("\nGoodbye!\n\n");
      break;
    }

    switch (choice) {
      case 0:
        printf("\nGoodbye!\n\n");
        break;
      case 1:
        printf("\nEnter the name of an input file to use: ");
        scanf("%s", database_file);
        database_fp = fopen(database_file, "rb+");

        while (database_fp == NULL) {
          printf("Unable to open %s for input.\n", database_file);
          printf("\nEnter the name of an input file to use: ");
          scanf("%s", database_file);
          database_fp = fopen(database_file, "rb+");
        }
        printf("\nEnter offset to read: ");
        read = scanf("%d%c", &n, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("\nEnter offset to read: ");
          read = scanf("%d%c", &n, &c);
        }
        prof = read_professor(database_fp, n);
        printf("\nThe professor record returned is \n");
        print_professor(prof);
        break;
      case 2:
        printf("\nEnter the name of an input file to use: ");
        scanf("%s", database_file);
        database_fp = fopen(database_file, "rb+");

        while (database_fp == NULL) {
          printf("Unable to open %s for input.\n", database_file);
          printf("\nEnter the name of an input file to use: ");
          scanf("%s", database_file);
          database_fp = fopen(database_file, "rb+");
        }
        printf("\nEnter offset to write: ");
        read = scanf("%d%c", &n, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("\nEnter offset to write: ");
          read = scanf("%d%c", &n, &c);
        }
        printf("\nEnter a file containing a professor representation: ");
        fscanf(stdin, "\n%s", prof_file);
        prof = read_professor_from_file(prof_file);
        printf("\nRead the following information:\n");
        print_professor(prof);
        value = write_professor(database_fp, prof, n);
        printf("\nThe value returned is %d.\n", value);
        break;
      case 3:
        printf("\nEnter the name of an input file to use: ");
        scanf("%s", database_file);
        database_fp = fopen(database_file, "rb+");

        while (database_fp == NULL) {
          printf("Unable to open %s for input.\n", database_file);
          printf("\nEnter the name of an input file to use: ");
          scanf("%s", database_file);
          database_fp = fopen(database_file, "rb+");
        }
        f_value = compute_female_percent(database_fp);
        printf("\nThe value returned is %.4f%%.\n", f_value * 100);
        break;
      case 4:
        printf("\nEnter the name of an input file to use: ");
        scanf("%s", database_file);
        database_fp = fopen(database_file, "rb+");

        while (database_fp == NULL) {
          printf("Unable to open %s for input.\n", database_file);
          printf("\nEnter the name of an input file to use: ");
          scanf("%s", database_file);
          database_fp = fopen(database_file, "rb+");
        }
        f_value = total_funding_by_male(database_fp);
        printf("\nThe value returned is %.4f.\n", f_value);
        break;
      case 5:
        printf("\nEnter the name of an input file to use: ");
        scanf("%s", database_file);
        database_fp = fopen(database_file, "rb+");

        while (database_fp == NULL) {
          printf("Unable to open %s for input.\n", database_file);
          printf("\nEnter the name of an input file to use: ");
          scanf("%s", database_file);
          database_fp = fopen(database_file, "rb+");
        }
        printf("\nEnter the first name: ");
        scanf("%s", first_name);
        printf("\nEnter the last name: ");
        scanf("%s", last_name);

        value = find_professor_by_name(database_fp, first_name, last_name);
        printf("\nThe value returned is %d.\n", value);
        break;
      case 6:
        printf("\nEnter the name of an input file to use: ");
        scanf("%s", database_file);
        database_fp = fopen(database_file, "rb+");

        while (database_fp == NULL) {
          printf("Unable to open %s for input.\n", database_file);
          printf("\nEnter the name of an input file to use: ");
          scanf("%s", database_file);
          database_fp = fopen(database_file, "rb+");
        }
        printf("\nEnter the id number: ");
        read = scanf("%d%c", &id, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("\nEnter the id number: ");
          read = scanf("%d%c", &id, &c);
        }

        value = find_professor_by_id(database_fp, id);
        printf("\nThe value returned is %d.\n", value);
        break;
      case 7:
        printf("\nEnter the name of an input file to use: ");
        scanf("%s", database_file);
        database_fp = fopen(database_file, "rb+");

        while (database_fp == NULL) {
          printf("Unable to open %s for input.\n", database_file);
          printf("\nEnter the name of an input file to use: ");
          scanf("%s", database_file);
          database_fp = fopen(database_file, "rb+");
        }
        printf("\nEnter the age: ");
        read = scanf("%d%c", &age, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("\nEnter the age: ");
          read = scanf("%d%c", &age, &c);
        }

        f_value = average_funding_by_age(database_fp, age);
        printf("\nThe value returned is %.4f.\n", f_value);
        break;
      case 8:
        printf("\nEnter the name of an input file to use: ");
        scanf("%s", database_file);
        database_fp = fopen(database_file, "rb+");

        while (database_fp == NULL) {
          printf("Unable to open %s for input.\n", database_file);
          printf("\nEnter the name of an input file to use: ");
          scanf("%s", database_file);
          database_fp = fopen(database_file, "rb+");
        }

        printf("\nEnter the id number: ");
        read = scanf("%d%c", &id, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("\nEnter the id number: ");
          read = scanf("%d%c", &id, &c);
        }

        value = fund_student(database_fp, id);
        printf("\nThe value returned is %d.\n", value);
        break;
      case 9:
        printf("\nEnter the name of an input file to use: ");
        scanf("%s", database_file);
        database_fp = fopen(database_file, "rb+");

        while (database_fp == NULL) {
          printf("Unable to open %s for input.\n", database_file);
          printf("\nEnter the name of an input file to use: ");
          scanf("%s", database_file);
          database_fp = fopen(database_file, "rb+");
        }
        printf("\nEnter the first id number: ");
        read = scanf("%d%c", &id1, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("\nEnter the first id number: ");
          read = scanf("%d%c", &id1, &c);
        }

        printf("\nEnter the second id number: ");
        read = scanf("%d%c", &id2, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("\nEnter the first id number: ");
          read = scanf("%d%c", &id2, &c);
        }

        value = schedule_meeting(database_fp, id1, id2);
        printf("\nThe value returned is %d.\n", value);
        break;
      default:
        printf("\nInvalid selection.\n");
        break;
    }
  }

  return 0;
} /* main() */


/*
 * Function to read in information about a professor
 */

professor_t read_professor_from_file(char *file_name) {
  FILE *fp = fopen(file_name, "r");
  professor_t prof = BAD_PROFESSOR;
  if (fp == NULL) {
    return prof;
  }
  if (fscanf(fp, "%d\n", &prof.id_number) != 1) {
    return prof;
  }
  if (fscanf(fp, "%19[^\n]\n", prof.first_name) != 1) {
    return prof;
  }
  if (fscanf(fp, "%19[^\n]\n", prof.last_name) != 1) {
    return prof;
  }
  if (fscanf(fp, "%d\n", &prof.age) != 1) {
    return prof;
  }
  if (fscanf(fp, "%f\n", &prof.funding) != 1) {
    return prof;
  }
  if (fscanf(fp, "%d\n", ((int *)&prof.gender)) != 1) {
    return prof;
  }
  for (int i = 0; i < N_DAYS; i++) {
    for (int j = 0; j < N_HOURS; j++) {
      if (fscanf(fp, "%c", &prof.class[i][j]) != 1) {
        return prof;
      }
    }
    if (fscanf(fp, "\n") != 0) {
      return prof;
    }
  }
  return prof;
} /* read_professor_from_file() */

