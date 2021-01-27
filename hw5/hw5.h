#ifndef HW5_H
#define HW5_H

#include <stdio.h>

/* Constant definitions */
#define MAX_NAME_LEN    (20)  /* Max length of any string */
#define N_DAYS          (5)
#define N_HOURS         (14)

/* Error codes */
#define OK                (-1)   /* No errors, everything as should be */
#define NO_PROFESSOR      (-2)
#define NO_OVERLAP        (-3)
#define NO_FUNDING        (-4)
#define WRITE_ERROR       (-5)

#define BAD_PROFESSOR ((professor_t){\
  .id_number = -1,\
  .first_name = "BOGUS",\
  .last_name = "BOGUS",\
  .age = -1,\
  .funding = -1.0,\
  .gender = -1,\
  .class[N_DAYS - 1][N_HOURS - 1] = 'Y'})

enum gender_t {
  FEMALE,
  MALE,
  OTHER,
};

/* Structure Declarations */B3| Black :??|??|D4|D2|A5|C5|A1|C1 B5| Black :??|??|D6|D4|A7|C7|A3|C3 C2|White:A3|A1|E3|E1|B4|D4|??|?? C6|White:A7|A5|E7|E5|B8|D8|B4|D4 D4|White:B5|B3|F5|F3|C6|E6|C2|E2 E2| Black :C3|C1|G3|G1|D4|F4|??|?? E6| Black :C7|C5|G7|G5|D8|F8|D4|F4 ter
typedef struct {
  int id_number;
  char first_name[MAX_NAME_LEN];
  char last_name[MAX_NAME_LEN];
  int age;
  float funding;
  enum gender_t gender;
  char class[N_DAYS][N_HOURS];
} professor_t;

/* Function prototypes */
professor_t read_professor(FILE *, int);
int write_professor(FILE *, professor_t, int);
float compute_female_percent(FILE *);
float total_funding_by_male(FILE *);
int find_professor_by_name(FILE *, char *, char *);
int find_professor_by_id(FILE *, int);
float average_funding_by_age(FILE *, int);
int fund_student(FILE *, int);
int schedule_meeting(FILE *, int, int);

#endif // HW5_H
