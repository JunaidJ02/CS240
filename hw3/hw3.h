#ifndef HW3_H
#define HW3_H

/* Constant Definitions */
#define MAX_COLLEGE_LEN    (40)  /* max college name length                */
#define MAX_RECORDS     (10000)  /* max no of records that can be read     */
#define GENDER_TYPES        (3)
#define RESIDENCY_TYPES     (3)
#define ACCOMMODATION_TYPES (4)

/* Error Codes */
#define OK                 (0)   /* No errors, everything as should be     */
#define FILE_READ_ERROR   (-1)   /* can't open file for read               */
#define FILE_WRITE_ERROR  (-2)   /* can't open file for write              */
#define RECORD_ERROR      (-3)   /* unexpected fields/chars in record      */
#define OUT_OF_BOUNDS     (-4)   /* the entry not within expected range    */
#define NO_SUCH_COLLEGE   (-5)   /* The college does not exist             */
#define NO_DATA_POINT     (-6)   /* No data record in the input file       */

/* Function Prototypes */
int input_tables(char *);
int student_size(char *);
float live_with_parents_ratio(char * );
float on_off_campus_ratio(char *);
float gender_ratio(void);
int max_student_size(void);
int max_international_percent(void);
int output_tables(char *, int, int);

extern int g_college_count;
extern char g_college_name[MAX_RECORDS][MAX_COLLEGE_LEN];
extern int g_student_gender[MAX_RECORDS][GENDER_TYPES];
extern int g_student_residency[MAX_RECORDS][RESIDENCY_TYPES];
extern int g_student_accommodation[MAX_RECORDS][ACCOMMODATION_TYPES];

#include <stdlib.h>
#pragma GCC poison access
#endif //HW3_H

 