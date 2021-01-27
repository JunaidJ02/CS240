#ifndef HW2_H
#define HW2_H

/* Constant Definitions */
#define MAX_FILE_LEN (40)     /* The maximum file name length */
#define MAX_NAME_LEN (40)     /* The maximum length of name string */
#define MAX_AREA_LEN (40)     /* The maximum length of area string */

/* Error Codes */
#define OK (0)                /* No errors, everything as should be */
#define BAD_RECORD (-1)       /* Record is somehow malformed */
#define BAD_DATE (-2)         /* Year must be nonnegative
                                 Month is not with the range 1-12
                                 Day is not with the range 1-31 */
#define BAD_CUTOFF (-3)       /* Cutoff values must be nonnegative */
#define FILE_READ_ERROR (-4)  /* Error reading from a file */
#define FILE_WRITE_ERROR (-5) /* Error writing to a file */
#define NO_DATA_POINT (-6)    /* No data points */

/* Function Prototypes */
int get_month_sold(char *, int, int);
int get_max_sold(char *);
int get_auction_list(char *, char *, int);
int compare_price(char *, char *, char *, int, int);
float get_area_average(char *, char *);

#pragma GCC poison access

#endif // HW2_H
